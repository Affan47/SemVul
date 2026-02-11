__gf_rdma_send_reply_type_msg (gf_rdma_peer_t *peer, gf_rdma_ioq_t *entry,
                               gf_rdma_post_t *post, gf_rdma_reply_info_t *reply_info)
{
        gf_rdma_header_t      *header       = NULL;
        int32_t             send_size    = 0, ret = 0;
        char               *ptr          = NULL;
        uint32_t            payload_size = 0;

        send_size = iov_length (entry->rpchdr, entry->rpchdr_count)
                + iov_length (entry->proghdr, entry->proghdr_count)
                + GLUSTERFS_RDMA_MAX_HEADER_SIZE;

        if (send_size > GLUSTERFS_RDMA_INLINE_THRESHOLD) {
                gf_log (GF_RDMA_LOG_NAME, GF_LOG_WARNING,
                        "client has provided only write chunks, but the "
                        "combined size of rpc and program header (%d) is "
                        "exceeding the size of msg that can be sent using "
                        "RDMA send (%d)", send_size,
                        GLUSTERFS_RDMA_INLINE_THRESHOLD);

                ret = __gf_rdma_send_error (peer, entry, post, reply_info,
                                            ERR_CHUNK);
                goto out;
        }

        header = (gf_rdma_header_t *)post->buf;

        __gf_rdma_fill_reply_header (header, entry->rpchdr, reply_info,
                                     peer->send_count);

        payload_size = iov_length (entry->prog_payload,
                                   entry->prog_payload_count);
        ptr = (char *)&header->rm_body.rm_chunks[1];

        ret = __gf_rdma_reply_encode_write_chunks (peer, payload_size, post,
                                                   reply_info,
                                                   (uint32_t **)&ptr);
        if (ret == -1) {
                gf_log (GF_RDMA_LOG_NAME, GF_LOG_DEBUG,
                        "encoding write chunks failed");
                ret = __gf_rdma_send_error (peer, entry, post, reply_info,
                                            ERR_CHUNK);
                goto out;
        }

        *(uint32_t *)ptr = 0;
        ptr += sizeof (uint32_t);

        gf_rdma_post_ref (post);

        ret = __gf_rdma_do_gf_rdma_write (peer, post, entry->prog_payload,
                                          entry->prog_payload_count,
                                          entry->iobref, reply_info);
        if (ret == -1) {
                gf_rdma_post_unref (post);
                goto out;
        }

        iov_unload (ptr, entry->rpchdr, entry->rpchdr_count);
        ptr += iov_length (entry->rpchdr, entry->rpchdr_count);

        iov_unload (ptr, entry->proghdr, entry->proghdr_count);
        ptr += iov_length (entry->proghdr, entry->proghdr_count);

        ret = gf_rdma_post_send (peer->qp, post, (ptr - post->buf));
        if (ret) {
                gf_log (GF_RDMA_LOG_NAME, GF_LOG_WARNING,
                        "rdma send to client (%s) failed with ret = %d (%s)",
                        peer->trans->peerinfo.identifier, ret,
                        (ret > 0) ? strerror (ret) : "");
                gf_rdma_post_unref (post);
                ret = -1;
        } else {
                ret = send_size + payload_size;
        }

out:
        return ret;
}
