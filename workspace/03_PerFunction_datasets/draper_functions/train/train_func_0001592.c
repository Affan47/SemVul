insert_freq(GHashTable *h, fs_quad_freq *f)
{
    fs_quad_freq *old = (fs_quad_freq *)g_hash_table_lookup(h, f);
    if (old) {
        old->freq += f->freq;
    } else {
        g_hash_table_insert(h, f, f);
    }
    fs_quad_freq ponly = *f;
    ponly.sec = FS_RID_NULL;
    old = (fs_quad_freq *)g_hash_table_lookup(h, &ponly);
    if (!old) {
        old = calloc(1, sizeof(fs_quad_freq));
        old->pri = ponly.pri;
        old->sec = ponly.sec;
        g_hash_table_insert(h, old, old);
    }
    old->freq += ponly.freq;
}
