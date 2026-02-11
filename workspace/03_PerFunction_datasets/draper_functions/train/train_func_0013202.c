_parse_file_properties(int fd, struct asf_info *info)
{
    struct {
        char fileid[16];
        uint64_t file_size;
        uint64_t creation_date;
        uint64_t data_packets_count;
        uint64_t play_duration;
        uint64_t send_duration;
        uint64_t preroll;
        uint32_t flags;
        uint32_t min_data_packet_size;
        uint32_t max_data_packet_size;
        uint32_t max_bitrate;
    } __attribute__((packed)) props;
    int r;

    r = read(fd, &props, sizeof(props));
    if (r != sizeof(props))
        return r;


    if (le32toh(props.flags) & 0x1)
        return r;


    info->length = (unsigned int)(
        (le64toh(props.play_duration) / NSEC100_PER_SEC) -
        le64toh(props.preroll) / MSEC_PER_SEC);

    return r;
}
