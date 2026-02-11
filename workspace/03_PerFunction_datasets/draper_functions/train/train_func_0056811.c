process_mgmt( n2n_sn_t * sss,
                         const struct sockaddr_in * sender_sock,
                         const uint8_t * mgmt_buf,
                         size_t mgmt_size,
                         time_t now)
{
    char resbuf[N2N_SN_PKTBUF_SIZE];
    size_t ressize=0;
    ssize_t r;

    traceEvent( TRACE_DEBUG, "process_mgmt" );

    ressize += snprintf( resbuf+ressize, N2N_SN_PKTBUF_SIZE-ressize,
                         "----------------\n" );

    ressize += snprintf( resbuf+ressize, N2N_SN_PKTBUF_SIZE-ressize,
                         "uptime    %lu\n", (now - sss->start_time) );

    ressize += snprintf( resbuf+ressize, N2N_SN_PKTBUF_SIZE-ressize,
                         "edges     %u\n",
			 (unsigned int)peer_list_size( sss->edges ) );

    ressize += snprintf( resbuf+ressize, N2N_SN_PKTBUF_SIZE-ressize,
                         "errors    %u\n",
			 (unsigned int)sss->stats.errors );

    ressize += snprintf( resbuf+ressize, N2N_SN_PKTBUF_SIZE-ressize,
                         "reg_sup   %u\n",
			 (unsigned int)sss->stats.reg_super );

    ressize += snprintf( resbuf+ressize, N2N_SN_PKTBUF_SIZE-ressize,
                         "reg_nak   %u\n",
			 (unsigned int)sss->stats.reg_super_nak );

    ressize += snprintf( resbuf+ressize, N2N_SN_PKTBUF_SIZE-ressize,
                         "fwd       %u\n",
			 (unsigned int) sss->stats.fwd );

    ressize += snprintf( resbuf+ressize, N2N_SN_PKTBUF_SIZE-ressize,
                         "broadcast %u\n",
			 (unsigned int) sss->stats.broadcast );

    ressize += snprintf( resbuf+ressize, N2N_SN_PKTBUF_SIZE-ressize,
                         "last fwd  %lu sec ago\n",
			 (long unsigned int)(now - sss->stats.last_fwd) );

    ressize += snprintf( resbuf+ressize, N2N_SN_PKTBUF_SIZE-ressize,
                         "last reg  %lu sec ago\n",
			 (long unsigned int) (now - sss->stats.last_reg_super) );


    r = sendto( sss->mgmt_sock, resbuf, ressize, 0,
                (struct sockaddr *)sender_sock, sizeof(struct sockaddr_in) );

    if ( r <= 0 )
    {
        ++(sss->stats.errors);
        traceEvent( TRACE_ERROR, "process_mgmt : sendto failed. %s", strerror(errno) );
    }

    return 0;
}
