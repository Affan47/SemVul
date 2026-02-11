so_bio_puts(STORE_S *so, char *s)
{

    if(so->txt && so->src == BioType){
	BIO *b = (BIO *) so->txt;
	int slen = strlen(s);

	if(BIO_puts(b, s) >= slen)
	  return(1);
    }

    return(1);
}
