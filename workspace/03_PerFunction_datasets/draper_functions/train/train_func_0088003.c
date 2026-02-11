data_dumpnext(dns_engine_param_t *ep, dns_msg_resource_t *res, dns_engine_dump_t *edump)
{
    data_hash_t *hash;
    data_record_t *record, *p;
    data_config_t *conf = (data_config_t *) ep->ep_conf;
    data_pos_t *dpos = (data_pos_t *) edump->ed_data;

    if (sizeof(edump->ed_data) < sizeof(data_pos_t)) {
        plog(LOG_ERR, "%s: sizeof(edump->ed_data) < sizeof(data_pos_t)", MODULE);
        return -1;
    }

    if (data_dump_checkpos(dpos, conf) < 0) {
        if (data_dump_nextpos(dpos, conf) < 0)
            return -1;
    }

    hash = &conf->conf_hash[dpos->dp_hashi];
    if ((record = data_hash_record(conf, hash)) == NULL)
        return -1;

    p = &record[dpos->dp_datai];
    if (data_record2res(res, conf, p) < 0)
        return -1;

    data_dump_nextpos(dpos, conf);

    return 0;
}
