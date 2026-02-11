qcow_aio_read_cb(void *opaque, int ret)
{
    QCowAIOCB *acb = opaque;
    BlockDriverState *bs = acb->common.bs;
    BDRVQcowState *s = bs->opaque;
    int index_in_cluster;

    acb->hd_aiocb = NULL;
    if (ret < 0) {
    fail:
        acb->common.cb(acb->common.opaque, ret);
        qemu_aio_release(acb);
        return;
    }

 redo:

    if (!acb->cluster_offset) {

    } else if (acb->cluster_offset & QCOW_OFLAG_COMPRESSED) {

    } else {
        if (s->crypt_method) {
            encrypt_sectors(s, acb->sector_num, acb->buf, acb->buf,
                            acb->n, 0,
                            &s->aes_decrypt_key);
        }
    }

    acb->nb_sectors -= acb->n;
    acb->sector_num += acb->n;
    acb->buf += acb->n * 512;

    if (acb->nb_sectors == 0) {

        acb->common.cb(acb->common.opaque, 0);
        qemu_aio_release(acb);
        return;
    }


    acb->cluster_offset = get_cluster_offset(bs, acb->sector_num << 9,
                                             0, 0, 0, 0);
    index_in_cluster = acb->sector_num & (s->cluster_sectors - 1);
    acb->n = s->cluster_sectors - index_in_cluster;
    if (acb->n > acb->nb_sectors)
        acb->n = acb->nb_sectors;

    if (!acb->cluster_offset) {
        if (bs->backing_hd) {

            acb->hd_aiocb = bdrv_aio_read(bs->backing_hd,
                acb->sector_num, acb->buf, acb->n, qcow_aio_read_cb, acb);
            if (acb->hd_aiocb == NULL)
                goto fail;
        } else {

            memset(acb->buf, 0, 512 * acb->n);
            goto redo;
        }
    } else if (acb->cluster_offset & QCOW_OFLAG_COMPRESSED) {

        if (decompress_cluster(s, acb->cluster_offset) < 0)
            goto fail;
        memcpy(acb->buf,
               s->cluster_cache + index_in_cluster * 512, 512 * acb->n);
        goto redo;
    } else {
        if ((acb->cluster_offset & 511) != 0) {
            ret = -EIO;
            goto fail;
        }
        acb->hd_aiocb = bdrv_aio_read(s->hd,
                            (acb->cluster_offset >> 9) + index_in_cluster,
                            acb->buf, acb->n, qcow_aio_read_cb, acb);
        if (acb->hd_aiocb == NULL)
            goto fail;
    }
}
