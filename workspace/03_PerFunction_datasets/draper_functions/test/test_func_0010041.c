ntru_max_msg_len(NtruEncParams *params) {
    uint16_t N = params->N;
    uint8_t llen = 1;
    uint16_t db = params->db;
    uint16_t max_msg_len;
    if (params->maxm1 > 0)
        max_msg_len = (N-1)*3/2/8 - llen - db/8;
    else
        max_msg_len = N*3/2/8 - llen - db/8;
    return max_msg_len;
}
