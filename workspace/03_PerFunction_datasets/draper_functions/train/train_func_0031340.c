keygen_add_notations(PKT_signature *sig,void *opaque)
{
  struct notation *notation;


  delete_sig_subpkt(sig->hashed,SIGSUBPKT_NOTATION);
  delete_sig_subpkt(sig->unhashed,SIGSUBPKT_NOTATION);
  sig->flags.notation=0;

  for(notation=opaque;notation;notation=notation->next)
    if(!notation->flags.ignore)
      {
	unsigned char *buf;
	unsigned int n1,n2;

	n1=strlen(notation->name);
	if(notation->altvalue)
	  n2=strlen(notation->altvalue);
	else if(notation->bdat)
	  n2=notation->blen;
	else
	  n2=strlen(notation->value);

	buf = xmalloc( 8 + n1 + n2 );


	buf[0] = notation->bdat?0:0x80;
	buf[1] = buf[2] = buf[3] = 0;
	buf[4] = n1 >> 8;
	buf[5] = n1;
	buf[6] = n2 >> 8;
	buf[7] = n2;
	memcpy(buf+8, notation->name, n1 );
	if(notation->altvalue)
	  memcpy(buf+8+n1, notation->altvalue, n2 );
	else if(notation->bdat)
	  memcpy(buf+8+n1, notation->bdat, n2 );
	else
	  memcpy(buf+8+n1, notation->value, n2 );
	build_sig_subpkt( sig, SIGSUBPKT_NOTATION |
			  (notation->flags.critical?SIGSUBPKT_FLAG_CRITICAL:0),
			  buf, 8+n1+n2 );
	xfree(buf);
      }

  return 0;
}
