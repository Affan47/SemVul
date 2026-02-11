handle_mlppp(const u_char *p, int length) {

    if (!eflag)
        printf("MLPPP, ");

    printf("seq 0x%03x, Flags [%s], length %u",
           (EXTRACT_16BITS(p))&0x0fff,
           bittok2str(ppp_ml_flag_values, "none", *p & 0xc0),
           length);

    return;
}
