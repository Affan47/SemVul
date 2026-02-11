raw_part_to_bio(long msgno, const char *section)
{
    unsigned long len;
    char	 *text;
    BIO          *bio;

    bio = BIO_new(BIO_s_mem());

    if(bio){

	(void) BIO_reset(bio);


        text = mail_fetch_mime(ps_global->mail_stream, msgno, (char*) section, &len, 0);

        if(text){
	    BIO_write(bio, text, len);


            text = mail_fetch_body (ps_global->mail_stream, msgno, (char*) section, &len, 0);
            if(text){
		BIO_write(bio, text, len);
	    }
	    else{
		BIO_free(bio);
		bio = NULL;
	    }

	}
	else{
	    BIO_free(bio);
	    bio = NULL;
	}
    }

    return bio;
}
