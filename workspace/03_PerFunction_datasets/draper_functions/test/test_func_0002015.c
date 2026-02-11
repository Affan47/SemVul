__gf_rdma_send_reply_inline (gf_rdma_peer_t *peer, gf_rdma_ioq_t *entry,
                             gf_rdma_post_t *post, gf_rdma_reply_info_t *reply_info)
{
        gf_rdma_header_t  *header    = NULL;
        int32_t         send_size = 0, ret = 0;
        char           *buf       = NULL;

        send_size = iov_length (entry->rpchdr, entry->rpchdr_count)
                + iov_length (entry->proghdr, entry->proghdr_count)
                + iov_length (entry->prog_payload, entry->prog_payload_count)
                + sizeof (gf_rdma_header_t);


        if (send_size > GLUSTERFS_RDMA_INLINE_THRESHOLD) {
                ret = __gf_rdma_send_error (peer, entry, post, reply_info,
                                            ERR_CHUNK);
                goto out;
        }

        header = (gf_rdma_header_t *)post->buf;

        __gf_rdma_fill_reply_header (header, entry->rpchdr, reply_info,
                                     peer->send_count);

        buf = (char *)&header->rm_body.rm_chunks[3];

        if (entry->rpchdr_count != 0) {
                iov_unload (buf, entry->rpchdr, entry->rpchdr_count);
                buf += iov_length (entry->rpchdr, entry->rpchdr_count);
        }

        if (entry->proghdr_count != 0) {
                iov_unload (buf, entry->proghdr, entry->proghdr_count);
                buf += iov_length (entry->proghdr, entry->proghdr_count);
        }

        if (entry->prog_payload_count != 0) {
                iov_unload (buf, entry->prog_payload,
                            entry->prog_payload_count);
                buf += iov_length (entry->prog_payload,
                                   entry->prog_payload_count);
        }

        gf_rdma_post_ref (post);

        ret = gf_rdma_post_send (peer->qp, post, (buf - post->buf));
        if (!ret) {
                ret = send_size;
        } else {
                gf_log (GF_RDMA_LOG_NAME, GF_LOG_WARNING,
                        "gf_rdma_post_send (to %s) failed with ret = %d (%s)",
                        peer->trans->peerinfo.identifier, ret,
                        (ret > 0) ? strerror (ret) : "");
                gf_rdma_post_unref (post);
                __gf_rdma_disconnect (peer->trans);
                ret = -1;
        }

out:
        return ret;
}
