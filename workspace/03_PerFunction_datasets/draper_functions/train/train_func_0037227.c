data_query_search_head(data_config_t *conf, data_hash_t *hash, dns_msg_question_t *q)
{
    int low, index;

    if ((low = data_query_bsearch(conf, hash, q)) < 0)
        return -1;
    if ((index = data_query_lsearch(conf, hash, q, low)) < 0)
        return -1;

    return index;
}
