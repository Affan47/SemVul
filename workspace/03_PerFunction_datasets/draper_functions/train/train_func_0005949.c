SetupSSL(void)
#else
SetupSSL()
#endif
{
    if (ctx == (SSL_CTX *)0) {
	char *ciphers;
	SSL_load_error_strings();
	if (!SSL_library_init()) {
	    Error("SetupSSL(): SSL_library_init() failed");
	    Bye(EX_SOFTWARE);
	}
	if ((ctx = SSL_CTX_new(SSLv23_method())) == (SSL_CTX *)0) {
	    Error("SetupSSL(): SSL_CTX_new() failed");
	    Bye(EX_SOFTWARE);
	}
	if (SSL_CTX_set_default_verify_paths(ctx) != 1) {
	    Error
		("SetupSSL(): could not load SSL default CA file and/or directory");
	    Bye(EX_SOFTWARE);
	}
	if (config->sslcredentials != (char *)0) {
	    if (SSL_CTX_use_certificate_chain_file
		(ctx, config->sslcredentials) != 1) {
		Error
		    ("SetupSSL(): could not load SSL certificate from `%s'",
		     config->sslcredentials);
		Bye(EX_SOFTWARE);
	    }
	    if (SSL_CTX_use_PrivateKey_file
		(ctx, config->sslcredentials, SSL_FILETYPE_PEM) != 1) {
		Error
		    ("SetupSSL(): could not load SSL private key from `%s'",
		     config->sslcredentials);
		Bye(EX_SOFTWARE);
	    }
	    ciphers = "ALL:!LOW:!EXP:!MD5:!aNULL:@STRENGTH";
	} else {
	    ciphers = "ALL:!LOW:!EXP:!MD5:@STRENGTH";
	}
	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, SSLVerifyCallback);
	SSL_CTX_set_options(ctx,
			    SSL_OP_ALL | SSL_OP_NO_SSLv2 |
			    SSL_OP_SINGLE_DH_USE);
	SSL_CTX_set_mode(ctx,
			 SSL_MODE_ENABLE_PARTIAL_WRITE |
			 SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER |
			 SSL_MODE_AUTO_RETRY);
	SSL_CTX_set_tmp_dh_callback(ctx, TmpDHCallback);
	if (SSL_CTX_set_cipher_list(ctx, ciphers) != 1) {
	    Error("SetupSSL(): setting SSL cipher list failed");
	    Bye(EX_SOFTWARE);
	}


	SSL_CTX_set_session_cache_mode(ctx, SSL_SESS_CACHE_OFF);
    }
}
