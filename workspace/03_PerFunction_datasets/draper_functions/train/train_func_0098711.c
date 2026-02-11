decode_channel_map(enum ChannelPosition *cpe_map,
        enum ChannelPosition *sce_map, enum ChannelPosition type, GetBitContext * gb, int n) {
    while(n--) {
        enum ChannelPosition *map = cpe_map && get_bits1(gb) ? cpe_map : sce_map;
        map[get_bits(gb, 4)] = type;
    }
}
