ns_mta_hash_alg(char *buffer, char *salt, const char *passwd)
{
  mta_MD5_CTX context;
  char *saltstr;
  unsigned char digest[16];


	if ( (saltstr = slapi_ch_malloc(strlen(salt)*2 + strlen(passwd) + 3))
		== NULL ) {
		return( NULL );
	}

  sprintf(saltstr,"%s%c%s%c%s",salt,89,passwd,247,salt);

  mta_MD5Init(&context);
  mta_MD5Update(&context,(unsigned char *)saltstr,strlen(saltstr));
  mta_MD5Final(digest,&context);
  ns_mta_hexify(buffer,(char*)digest,16);
  buffer[32] = '\0';
  slapi_ch_free((void**)&saltstr);
  return(buffer);

}
