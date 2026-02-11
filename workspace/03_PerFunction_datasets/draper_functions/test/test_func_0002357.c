filter_match( struct filter *filt, struct tcp_connection *conn_p )
{
        int rv = 0;

        filt->evals++;

        if ( filt->policy & POLICY_AF ) {
                if ( conn_p->laddr.ss_family != filt->af ||
                     conn_p->raddr.ss_family != filt->af ) {
                        rv = 0;
                        TRACE("Address family didn't match!\n");
                        return rv;
                }
        }

        if ( filt->policy & POLICY_IF ) {
          if ( conn_p->metadata.ifname == NULL ||
              filt->ifname == NULL ) {
            WARN("Filtering by IF, yet NULL ifname\n" );
            rv = 1;
          } else if ( strcmp(conn_p->metadata.ifname, filt->ifname) == 0 ) {
            TRACE("interface name matched\n" );
            rv = 1;
          } else {
            return rv;
          }
        }

        if ( filt->policy & POLICY_CLOUD ) {
                TRACE("Cloud stamps, filter: %ld, conn %ld \n", filt->cloud_stamp, conn_p->metadata.added );
                if ( conn_p->metadata.added - filt->cloud_stamp< CLOUD_TIME_LIMIT ) {
                        TRACE("Difference %ld \n",filt->cloud_stamp - conn_p->metadata.added);
                        TRACE("Cloud timestamp in the limit\n");
                        rv = 1;
                } else {
                        TRACE("Cloud didn't match");
                        return 0;
                }
        }

        if ( filt->policy & POLICY_LOCAL ) {
                rv = match_saddr( LADDR(filt), LADDR(conn_p), filt->policy );
                if ( rv == 0 ) {
                        TRACE("Local saddr didn't match!\n");
                        return rv;
                }
        }
        if ( filt->policy & POLICY_REMOTE ) {
                rv = match_saddr( RADDR(filt), RADDR(conn_p), filt->policy );
                if ( rv == 0 ) {
                        TRACE("Local saddr didn't match!\n");
                        return rv;
                }
        }

        if ( filt->policy & POLICY_STATE ) {
                if ( filt->state == conn_p->state )
                        rv = 1;
        }

        TRACE( "Match result %d\n", rv );
        if ( rv )
                filt->matches++;
        return rv;
}
