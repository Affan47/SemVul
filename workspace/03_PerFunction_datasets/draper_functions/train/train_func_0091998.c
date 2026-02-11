verify_bom_signature(AFFILE *af,const char *buf)
{
    OpenSSL_add_all_digests();
    const EVP_MD *sha256 = EVP_get_digestbyname("sha256");

    if(!sha256){
	fprintf(stderr,"OpenSSL does not have SHA256; signatures cannot be verified.\n");
	return -1;
    }

    const char *cce = "</" AF_XML_AFFBOM ">\n";
    const char *chain_end = strstr(buf,cce);
    if(!chain_end){
	warn("end of chain XML can't be found\n");
	return -1;
    }
    const char *sig_start = chain_end + strlen(cce);

    BIO *seg = BIO_new_mem_buf((void *)buf,strlen(buf));
    if(BIO_seek(seg,0)!=0){
	printf("Cannot seek to beginning of BIO mem?");
	return -1;
    }
    X509 *cert = 0;
    PEM_read_bio_X509(seg,&cert,0,0);
    BIO_free(seg);


    u_char sigbuf[1024];
    int sigbuf_len = b64_pton_slg(sig_start,strlen(sig_start),sigbuf,sizeof(sigbuf));
    if(sigbuf_len<80){
	warn("BOM is not signed");
	return -1;
    }


    EVP_MD_CTX md;
    EVP_VerifyInit(&md,sha256);
    EVP_VerifyUpdate(&md,buf,sig_start-buf);
    int r = EVP_VerifyFinal(&md,sigbuf,sigbuf_len,X509_get_pubkey(cert));
    if(r!=1){
	printf("BAD SIGNATURE ON BOM\n");
	return -1;
    }

    print_x509_info(cert);
    printf("Date: %s\n",get_xml_field(buf,"date").c_str());
    printf("Notes: \n%s\n",get_xml_field(buf,"notes").c_str());


    char *buffer_without_signature = strdup(buf);
    char *sigend = strstr(buffer_without_signature,cce);
    if(sigend){
	sigend[strlen(cce)] = 0;
    }

    segmenthash sh;
    sh.af = af;
    if (!sh.parse(buffer_without_signature, strlen(buffer_without_signature))){
	fprintf(stderr, "expat error: %s at line %d\n",
		XML_ErrorString(XML_GetErrorCode(sh.parser)),
		(int)XML_GetCurrentLineNumber(sh.parser));
	fprintf(stderr,"buffer without signature:\n%s\n",buffer_without_signature);
	return 1;
    }
    free(buffer_without_signature);
    return 0;
}
