OTF_Writer_closeAllStreams( OTF_Writer* writer ) {


	int ret= 1;
	uint32_t i;

	for ( i= 0; i < writer->n; ++i ) {

		ret&= OTF_WStream_close( writer->streams[i] );
	}

	writer->n= 0;

	return ret;
}
