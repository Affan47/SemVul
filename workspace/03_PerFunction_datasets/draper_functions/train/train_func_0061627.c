base64_decode(char *enc,char *dec,int decsize)
{
    int i,j;
    char dtable[256];


    for( i = 0; i < 255; i++) {
	dtable[i] = 0x80;
    }
    for(i = 'A' ; i <= 'Z'; i++) {
	dtable[i] = 0 + (i - 'A');
    }
    for(i = 'a' ; i <= 'z'; i++) {
	dtable[i] = 26 + (i - 'a');
    }
    for(i = '0' ; i <= '9'; i++) {
	dtable[i] = 52 + (i - '0');

    }
    dtable['+'] = 62;
    dtable['/'] = 63;
    dtable['='] = 0;


    for(i = j = 0; i<strlen(enc) ; i += 4) {
	char input[4], output[3];

	input[0] = dtable[(enc[i + 0] & 0xff)];
	input[1] = dtable[(enc[i + 1] & 0xff)];
	input[2] = dtable[(enc[i + 2] & 0xff)];
	input[3] = dtable[(enc[i + 3] & 0xff)];


	output[0] = (input[0] << 2) | (input[1] >> 4);
	output[1] = (input[1] << 4) | (input[2] >> 2);
	output[2] = (input[2] << 6) | (input[3]);

	if(j >= decsize) goto overflow;
	dec[j] = output[0];
	if(enc[i + 2] == '=') return j+1;

	if(j + 1 >= decsize) goto overflow;
	dec[j + 1] = output[1];
	if(enc[i + 3] == '=') return j+2;

	if(j + 2 >= decsize) goto overflow;
	dec[j + 2] = output[2];
	j += 3;
    }

    return j;

  overflow:
    display(MSDL_ERR,"internal error: base64 overflow!\n");
    return -1;
}
