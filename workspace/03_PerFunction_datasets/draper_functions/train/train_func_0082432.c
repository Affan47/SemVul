glusterd_set_clnt_mgmt_program (glusterd_peerinfo_t *peerinfo,
                                gf_prog_detail *prog)
{
        gf_prog_detail  *trav   = NULL;
        int             ret     = -1;

        if (!peerinfo || !prog)
                goto out;

        trav = prog;

        while (trav) {
                ret = -1;
                if ((gd_mgmt_prog.prognum == trav->prognum) &&
                    (gd_mgmt_prog.progver == trav->progver)) {
                        peerinfo->mgmt = &gd_mgmt_prog;
                        ret = 0;
                }

                if ((gd_peer_prog.prognum == trav->prognum) &&
                    (gd_peer_prog.progver == trav->progver)) {
                        peerinfo->peer = &gd_peer_prog;
                        ret = 0;
                }

                if (ret) {
                        gf_log ("", GF_LOG_DEBUG,
                                "%s (%"PRId64":%"PRId64") not supported",
                                trav->progname, trav->prognum,
                                trav->progver);
                }

                trav = trav->next;
        }

        if (peerinfo->mgmt) {
                 gf_log ("", GF_LOG_INFO,
                         "Using Program %s, Num (%d), Version (%d)",
                         peerinfo->mgmt->progname, peerinfo->mgmt->prognum,
                         peerinfo->mgmt->progver);
        }

        if (peerinfo->peer) {
                 gf_log ("", GF_LOG_INFO,
                         "Using Program %s, Num (%d), Version (%d)",
                         peerinfo->peer->progname, peerinfo->peer->prognum,
                         peerinfo->peer->progver);
        }
        ret = 0;
out:
        return ret;

}
