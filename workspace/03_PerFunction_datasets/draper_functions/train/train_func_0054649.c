data_dump_checkpos(data_pos_t *dpos, data_config_t *conf)
{
    data_hash_t *hash;

    if (dpos->dp_hashi >= conf->conf_hashsize)
        return -1;

    hash = &conf->conf_hash[dpos->dp_hashi];
    if (dpos->dp_datai >= ntohl(hash->dh_count))
        return -1;

    return 0;
}
