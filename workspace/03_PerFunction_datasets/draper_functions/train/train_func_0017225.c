null_decoder_init(file_decoder_t * fdec) {

        decoder_t * dec = NULL;

        if ((dec = calloc(1, sizeof(decoder_t))) == NULL) {
                fprintf(stderr, "dec_null.c: null_decoder_new() failed: calloc error\n");
                return NULL;
        }

	dec->fdec = fdec;

        if ((dec->pdata = calloc(1, sizeof(null_pdata_t))) == NULL) {
                fprintf(stderr, "dec_null.c: null_decoder_new() failed: calloc error\n");
                return NULL;
        }

	dec->init = null_decoder_init;
	dec->destroy = null_decoder_destroy;
	dec->open = null_decoder_open;
	dec->send_metadata = null_decoder_send_metadata;
	dec->close = null_decoder_close;
	dec->read = null_decoder_read;
	dec->seek = null_decoder_seek;

	return dec;
}
