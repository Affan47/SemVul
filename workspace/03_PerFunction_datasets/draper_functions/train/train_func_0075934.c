tds_write_packet(TDSSOCKET * tds, unsigned char final)
{
	int sent;
	unsigned int left = 0;

#if !defined(_WIN32) && !defined(MSG_NOSIGNAL) && !defined(DOS32X) && (!defined(__APPLE__) || !defined(SO_NOSIGPIPE))
	void (*oldsig) (int);
#endif

#if TDS_ADDITIONAL_SPACE != 0
	if (tds->out_pos > tds->env.block_size) {
		left = tds->out_pos - tds->env.block_size;
		tds->out_pos = tds->env.block_size;
	}
#endif

	tds->out_buf[0] = tds->out_flag;
	tds->out_buf[1] = final;
	tds->out_buf[2] = (tds->out_pos) / 256u;
	tds->out_buf[3] = (tds->out_pos) % 256u;
	if (IS_TDS7_PLUS(tds) && !tds->connection)
		tds->out_buf[6] = 0x01;

	tdsdump_dump_buf(TDS_DBG_NETWORK, "Sending packet", tds->out_buf, tds->out_pos);

#if !defined(_WIN32) && !defined(MSG_NOSIGNAL) && !defined(DOS32X) && (!defined(__APPLE__) || !defined(SO_NOSIGPIPE))
	oldsig = signal(SIGPIPE, SIG_IGN);
	if (oldsig == SIG_ERR) {
		tdsdump_log(TDS_DBG_WARN, "TDS: Warning: Couldn't set SIGPIPE signal to be ignored\n");
	}
#endif

#ifdef HAVE_GNUTLS
	if (tds->tls_session)
		sent = gnutls_record_send(tds->tls_session, tds->out_buf, tds->out_pos);
	else
#elif defined(HAVE_OPENSSL)
	if (tds->tls_session)
		sent = SSL_write((SSL*) tds->tls_session, tds->out_buf, tds->out_pos);
	else
#endif
		sent = tds_goodwrite(tds, tds->out_buf, tds->out_pos, final);

#if !defined(_WIN32) && !defined(MSG_NOSIGNAL) && !defined(DOS32X) && (!defined(__APPLE__) || !defined(SO_NOSIGPIPE))
	if (signal(SIGPIPE, oldsig) == SIG_ERR) {
		tdsdump_log(TDS_DBG_WARN, "TDS: Warning: Couldn't reset SIGPIPE signal to previous value\n");
	}
#endif

#if TDS_ADDITIONAL_SPACE != 0
	memcpy(tds->out_buf + 8, tds->out_buf + tds->env.block_size, left);
#endif
	tds->out_pos = left + 8;


	return sent <= 0 ? TDS_FAIL : TDS_SUCCEED;
}
