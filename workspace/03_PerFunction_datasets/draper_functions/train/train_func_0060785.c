wav_read_data(void* obj, unsigned char* data, unsigned int length) {
	struct wav_reader* wr = (struct wav_reader*) obj;
	int n;
	if (wr->wav == NULL)
		return -1;
	if (length > wr->data_length)
		length = wr->data_length;
	n = fread(data, 1, length, wr->wav);
	wr->data_length -= length;
	return n;
}
