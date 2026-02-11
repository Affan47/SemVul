PrintMSS( ReporterData *stats ) {
    int inMSS = getsock_tcp_mss( stats->info.transferID );

    if ( inMSS <= 0 ) {
        printf( report_mss_unsupported, stats->info.transferID );
    } else {
        char* net;
        int mtu = 0;

        if ( checkMSS_MTU( inMSS, 1500 ) ) {
            net = "ethernet";
            mtu = 1500;
        } else if ( checkMSS_MTU( inMSS, 4352 ) ) {
            net = "FDDI";
            mtu = 4352;
        } else if ( checkMSS_MTU( inMSS, 9180 ) ) {
            net = "ATM";
            mtu = 9180;
        } else if ( checkMSS_MTU( inMSS, 65280 ) ) {
            net = "HIPPI";
            mtu = 65280;
        } else if ( checkMSS_MTU( inMSS, 576 ) ) {
            net = "minimum";
            mtu = 576;
            printf( "%s", warn_no_pathmtu );
        } else {
            mtu = inMSS + 40;
            net = "unknown interface";
        }

        printf( report_mss,
                stats->info.transferID, inMSS, mtu, net );
    }
}
