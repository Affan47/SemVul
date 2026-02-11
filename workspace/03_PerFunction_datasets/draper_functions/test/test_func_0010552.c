_tjInitDecompress(tjinstance *this)
{

	this->dinfo.err=jpeg_std_error(&this->jerr.pub);
	this->jerr.pub.error_exit=my_error_exit;
	this->jerr.pub.output_message=my_output_message;

	if(setjmp(this->jerr.setjmp_buffer))
	{

		if(this) free(this);  return NULL;
	}

	jpeg_create_decompress(&this->dinfo);
	this->dinfo.src=&this->jsrc;
	this->jsrc.init_source=src_noop;
	this->jsrc.fill_input_buffer=fill_input_buffer;
	this->jsrc.skip_input_data=skip_input_data;
	this->jsrc.resync_to_restart=jpeg_resync_to_restart;
	this->jsrc.term_source=src_noop;

	this->init|=DECOMPRESS;
	return (tjhandle)this;
}
