reporter_multistats( Transfer_Info *stats ) {

    byte_snprintf( buffer, sizeof(buffer)/2, (double) stats->TotalLen,
                   toupper( stats->mFormat));
    byte_snprintf( &buffer[sizeof(buffer)/2], sizeof(buffer)/2,
                   stats->TotalLen / (stats->endTime - stats->startTime),
                   stats->mFormat);

    if ( stats->mUDP != (char)kMode_Server ) {

        printf( report_sum_bw_format,
                stats->startTime, stats->endTime,
                buffer, &buffer[sizeof(buffer)/2] );
    } else {

        printf( report_sum_bw_jitter_loss_format,
                stats->startTime, stats->endTime,
                buffer, &buffer[sizeof(buffer)/2],
                stats->jitter*1000.0, stats->cntError, stats->cntDatagrams,
                (100.0 * stats->cntError) / stats->cntDatagrams );
        if ( stats->cntOutofOrder > 0 ) {
            printf( report_sum_outoforder,
                    stats->startTime,
                    stats->endTime, stats->cntOutofOrder );
        }
    }
    if ( stats->free == 1 && stats->mUDP == (char)kMode_Client ) {
        printf( report_sum_datagrams, stats->cntDatagrams );
    }
}
