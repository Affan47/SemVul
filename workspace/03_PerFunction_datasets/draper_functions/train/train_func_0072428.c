rescaleFreq8(Uint8 *source, int *src_len, Uint8 *dest, int dst_len)
{
	int srcSamplesRead=0, srcBytesRead=0;
	int dstSamplesWritten=0, dstBytesWritten=0;

	while ((srcBytesRead<*src_len) && (dstBytesWritten<dst_len)) {
		switch(srcChan) {
			case 2:
				dest[dstBytesWritten++] = source[srcBytesRead++];

			case 1:
				dest[dstBytesWritten++] = source[srcBytesRead];
				break;
		}

		srcSamplesRead = (dstSamplesWritten++ * srcRate) / dstRate;
		srcBytesRead = srcSamplesRead*srcSkip+srcOffset;
	}

	*src_len = srcBytesRead;
	return dstBytesWritten;
}
