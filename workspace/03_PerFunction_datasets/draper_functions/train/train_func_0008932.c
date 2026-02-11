bkn_dnx_packet_header_parse(uint8 *buff, uint32_t buff_len, bkn_dnx_packet_info *packet_info)
{
    uint8_t  hdr_buff[BKN_DNX_HDR_MAX_SIZE];
    uint32_t hdr_size;
    uint8_t  has_internal = 0;

    if ((buff == NULL) || (packet_info == NULL)) {
        return -1;
    }
    hdr_size = buff_len < BKN_DNX_HDR_MAX_SIZE ? buff_len: BKN_DNX_HDR_MAX_SIZE;
    memcpy(hdr_buff, buff, hdr_size);


    bkn_dnx_packet_parse_ftmh(hdr_buff, packet_info);
    if (packet_info->ftmh.packet_size != (buff_len + 2)) {
        DBG_DUNE(("FTMH packet size verfication failed, %d-%d\n", packet_info->ftmh.packet_size, buff_len));
        memset(packet_info, 0, sizeof(bkn_dnx_packet_info));
        return -1;
    }
    switch (packet_info->ftmh.pph_type) {
    case 0:
        has_internal = 0;
        break;
    case 1:
        has_internal = 1;
        break;
    case 2:
    case 3:

        packet_info->ntwrk_header_ptr +=  6;
        DBG_DUNE(("FTMH + OAM-TS(%d)\n", packet_info->ntwrk_header_ptr));
        has_internal = 1;
        break;
    default:
        break;
    }

    if (has_internal) {
      bkn_dnx_packet_parse_internal(&hdr_buff[0], packet_info);
    }


    return 0;
}
