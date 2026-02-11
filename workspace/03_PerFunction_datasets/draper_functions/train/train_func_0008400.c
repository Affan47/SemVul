nssToken_decodeSerialItem(NSSItem *serial, NSSItem *serialDecode)
{
    unsigned char *data = (unsigned char *)serial->data;
    int data_left, data_len, index;

    if ((serial->size >= 3) && (data[0] == 0x2)) {


	data_left = serial->size-2;
	data_len = data[1];
	index = 2;


	if (data_len & 0x80) {
	    int len_count = data_len & 0x7f;

	    data_len = 0;
	    data_left -= len_count;
	    if (data_left > 0) {
		while (len_count --) {
		    data_len = (data_len << 8) | data[index++];
		}
	    }
	}


	if (data_len == data_left) {
	    serialDecode->size = data_len;
	    serialDecode->data = &data[index];
	    return PR_SUCCESS;
	}
    }
    return PR_FAILURE;
}
