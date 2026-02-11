show_packets()
{
    SPRTF("%s: Packets %d, pos %d, discard %d, failed %d, chat %d.\n", module,
        (int)packet_cnt, (int)pos_cnt, (int)discard_cnt, (int)failed_cnt, (int)chat_cnt);
    if (VERB1) {
        double elap = get_seconds() - app_bgn_secs;
        if (elap > 0.0) {
            double rate = (double)packet_cnt / elap;
            SPRTF("%s: Rate %lf pkts/sec, elapsed %s\n", module,
                rate, get_seconds_stg(elap) );
        }
    }
}
