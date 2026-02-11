php_stream_filter_append_ex(php_stream_filter_chain *chain, php_stream_filter *filter TSRMLS_DC)
{
	php_stream *stream = chain->stream;

	filter->prev = chain->tail;
	filter->next = NULL;
	if (chain->tail) {
		chain->tail->next = filter;
	} else {
		chain->head = filter;
	}
	chain->tail = filter;
	filter->chain = chain;

	if (&(stream->readfilters) == chain && (stream->writepos - stream->readpos) > 0) {

		php_stream_bucket_brigade brig_in = { NULL, NULL }, brig_out = { NULL, NULL };
		php_stream_bucket_brigade *brig_inp = &brig_in, *brig_outp = &brig_out;
		php_stream_filter_status_t status;
		php_stream_bucket *bucket;
		size_t consumed = 0;

		bucket = php_stream_bucket_new(stream, (char*) stream->readbuf + stream->readpos, stream->writepos - stream->readpos, 0, 0 TSRMLS_CC);
		php_stream_bucket_append(brig_inp, bucket TSRMLS_CC);
		status = filter->fops->filter(stream, filter, brig_inp, brig_outp, &consumed, PSFS_FLAG_NORMAL TSRMLS_CC);

		if (stream->readpos + consumed > (uint)stream->writepos || consumed < 0) {

			status = PSFS_ERR_FATAL;
		}

		switch (status) {
			case PSFS_ERR_FATAL:
				while (brig_in.head) {
					bucket = brig_in.head;
					php_stream_bucket_unlink(bucket TSRMLS_CC);
					php_stream_bucket_delref(bucket TSRMLS_CC);
				}
				while (brig_out.head) {
					bucket = brig_out.head;
					php_stream_bucket_unlink(bucket TSRMLS_CC);
					php_stream_bucket_delref(bucket TSRMLS_CC);
				}
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Filter failed to process pre-buffered data");
				return FAILURE;
			case PSFS_FEED_ME:


				stream->readpos = 0;
				stream->writepos = 0;
				break;
			case PSFS_PASS_ON:


				stream->writepos = 0;
				stream->readpos = 0;

				while (brig_outp->head) {
					bucket = brig_outp->head;


					if (stream->readbuflen - stream->writepos < bucket->buflen) {
						stream->readbuflen += bucket->buflen;
						stream->readbuf = perealloc(stream->readbuf, stream->readbuflen, stream->is_persistent);
					}
					memcpy(stream->readbuf + stream->writepos, bucket->buf, bucket->buflen);
					stream->writepos += bucket->buflen;

					php_stream_bucket_unlink(bucket TSRMLS_CC);
					php_stream_bucket_delref(bucket TSRMLS_CC);
				}
				break;
		}
	}

	return SUCCESS;
}
