__dht_rebalance_migrate_data (xlator_t *from, xlator_t *to, fd_t *src, fd_t *dst,
                             uint64_t ia_size, int hole_exists)
{
        int            ret    = 0;
        int            count  = 0;
        off_t          offset = 0;
        struct iovec  *vector = NULL;
        struct iobref *iobref = NULL;
        uint64_t       total  = 0;
        size_t         read_size = 0;


        while (total < ia_size) {
                read_size = (((ia_size - total) > DHT_REBALANCE_BLKSIZE) ?
                             DHT_REBALANCE_BLKSIZE : (ia_size - total));
                ret = syncop_readv (from, src, read_size,
                                    offset, &vector, &count, &iobref);
                if (!ret || (ret < 0)) {
                        break;
                }

                if (hole_exists)
                        ret = dht_write_with_holes (to, dst, vector, count,
                                                    ret, offset, iobref);
                else
                        ret = syncop_writev (to, dst, vector, count,
                                             offset, iobref);
                if (ret < 0) {
                        break;
                }
                offset += ret;
                total += ret;

                if (vector)
                        GF_FREE (vector);
                if (iobref)
                        iobref_unref (iobref);
                iobref = NULL;
                vector = NULL;
        }
        if (iobref)
                iobref_unref (iobref);
        if (vector)
                GF_FREE (vector);

        if (ret >= 0)
                ret = 0;

        return ret;
}
