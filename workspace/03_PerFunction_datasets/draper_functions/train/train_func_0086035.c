e1000_mng_write_cmd_header(struct e1000_hw * hw,
                           struct e1000_host_mng_command_header * hdr)
{
    uint16_t i;
    uint8_t sum;
    uint8_t *buffer;


    uint16_t length = sizeof(struct e1000_host_mng_command_header);

    sum = hdr->checksum;
    hdr->checksum = 0;

    buffer = (uint8_t *) hdr;
    i = length;
    while (i--)
        sum += buffer[i];

    hdr->checksum = 0 - sum;

    length >>= 2;

    for (i = 0; i < length; i++) {
        E1000_WRITE_REG_ARRAY_DWORD(hw, HOST_IF, i, *((uint32_t *) hdr + i));
        E1000_WRITE_FLUSH(hw);
    }

    return E1000_SUCCESS;
}
