strusage( int level )
{
  static char *digests, *pubkeys, *ciphers, *zips;
    const char *p;
    switch( level ) {
      case 11: p = "gpg (GnuPG)";
	break;
      case 13: p = VERSION; break;
      case 17: p = PRINTABLE_OS_NAME; break;
      case 19: p =
	    _("Please report bugs to <gnupg-bugs@gnu.org>.\n");
	break;

#ifdef IS_DEVELOPMENT_VERSION
      case 20:
	p="NOTE: THIS IS A DEVELOPMENT VERSION!";
	break;
      case 21:
	p="It is only intended for test purposes and should NOT be";
	break;
      case 22:
	p="used in a production environment or with production keys!";
	break;
#endif

      case 1:
      case 40:	p =
	    _("Usage: gpg [options] [files] (-h for help)");
	break;
      case 41:	p =
	    _("Syntax: gpg [options] [files]\n"
	      "Sign, check, encrypt or decrypt\n"
	      "Default operation depends on the input data\n");
	break;

      case 31: p = "\nHome: "; break;
#ifndef __riscos__
      case 32: p = opt.homedir; break;
#else
      case 32: p = make_filename(opt.homedir, NULL); break;
#endif
      case 33: p = _("\nSupported algorithms:\n"); break;
      case 34:
	if( !pubkeys )
	    pubkeys = build_list(_("Pubkey: "), 0, pubkey_algo_to_string,
							check_pubkey_algo );
	p = pubkeys;
	break;
      case 35:
	if( !ciphers )
	    ciphers = build_list(_("Cipher: "), 'S', cipher_algo_to_string,
							check_cipher_algo );
	p = ciphers;
	break;
      case 36:
	if( !digests )
	    digests = build_list(_("Hash: "), 'H', digest_algo_to_string,
							check_digest_algo );
	p = digests;
	break;
      case 37:
	if( !zips )
	    zips = build_list(_("Compression: "),'Z',compress_algo_to_string,
			                                check_compress_algo);
	p = zips;
	break;

      default:	p = default_strusage(level);
    }
    return p;
}
