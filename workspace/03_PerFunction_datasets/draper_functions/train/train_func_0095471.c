get_data_len(unsigned char *pkey, int *index) {

	int data_len=0;
	int i,len_octet_count;

	if (pkey[(*index)++]&0x2) {

		if(pkey[(*index)] >= 128){

			len_octet_count = pkey[(*index)]^0x80;

			for(i=0;i<len_octet_count;i++) {

				data_len = data_len | pkey[++(*index)];
			}
			(*index)++;

		}else {

			data_len = pkey[(*index)];
			(*index)++;

		}
	}
	return data_len;

}
