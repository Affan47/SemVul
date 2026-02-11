nc_probe(AVProbeData *probe_packet)
{
    int size;

    if (AV_RB32(probe_packet->buf) != NC_VIDEO_FLAG)
        return 0;

    size = AV_RL16(probe_packet->buf + 5);

    if (size + 20 > probe_packet->buf_size)
        return 3*AVPROBE_SCORE_MAX/2;

    if (AV_RB32(probe_packet->buf+16+size) == NC_VIDEO_FLAG)
        return AVPROBE_SCORE_MAX;

    return 0;
}
