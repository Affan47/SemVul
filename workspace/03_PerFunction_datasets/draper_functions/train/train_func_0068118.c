dht_disk_layout_extract (xlator_t *this, dht_layout_t *layout,
                         int pos, int32_t **disk_layout_p)
{
        int      ret = -1;
        int32_t *disk_layout = NULL;

        disk_layout = GF_CALLOC (5, sizeof (int),
                                 gf_dht_mt_int32_t);
        if (!disk_layout) {
                goto out;
        }

        disk_layout[0] = hton32 (1);
        disk_layout[1] = hton32 (layout->type);
        disk_layout[2] = hton32 (layout->list[pos].start);
        disk_layout[3] = hton32 (layout->list[pos].stop);

        if (disk_layout_p)
                *disk_layout_p = disk_layout;
        else
                GF_FREE (disk_layout);

        ret = 0;

out:
        return ret;
}
