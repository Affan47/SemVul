write_signature_packets (SK_LIST sk_list, IOBUF out, MD_HANDLE hash,
                         int sigclass, u32 timestamp, u32 duration,
			 int status_letter)
{
    SK_LIST sk_rover;


    for (sk_rover = sk_list; sk_rover; sk_rover = sk_rover->next) {
	PKT_secret_key *sk;
	PKT_signature *sig;
	MD_HANDLE md;
        int rc;

	sk = sk_rover->sk;


	sig = xmalloc_clear (sizeof *sig);
	if(opt.force_v3_sigs || RFC1991)
	  sig->version=3;
	else if(duration || opt.sig_policy_url
		|| opt.sig_notations || opt.sig_keyserver_url)
	  sig->version=4;
	else
	  sig->version=sk->version;
	keyid_from_sk (sk, sig->keyid);
	sig->digest_algo = hash_for(sk);
	sig->pubkey_algo = sk->pubkey_algo;
	if(timestamp)
	  sig->timestamp = timestamp;
	else
	  sig->timestamp = make_timestamp();
	if(duration)
	  sig->expiredate = sig->timestamp+duration;
	sig->sig_class = sigclass;

	md = md_copy (hash);

	if (sig->version >= 4)
	  {
	    build_sig_subpkt_from_sig (sig);
	    mk_notation_policy_etc (sig, NULL, sk);
	  }

        hash_sigversion_to_magic (md, sig);
	md_final (md);

	rc = do_sign( sk, sig, md, hash_for (sk) );
	md_close (md);

	if( !rc ) {
            PACKET pkt;

	    init_packet(&pkt);
	    pkt.pkttype = PKT_SIGNATURE;
	    pkt.pkt.signature = sig;
	    rc = build_packet (out, &pkt);
	    if (!rc && is_status_enabled()) {
		print_status_sig_created ( sk, sig, status_letter);
	    }
	    free_packet (&pkt);
	    if (rc)
		log_error ("build signature packet failed: %s\n",
                           g10_errstr(rc) );
	}
	if( rc )
	    return rc;;
    }

    return 0;
}
