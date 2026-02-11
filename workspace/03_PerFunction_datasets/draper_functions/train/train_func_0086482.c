base64_encode_fp(FILE * fp, unsigned char *data,
		int datalen, int cpl)
{
    char out[100];
    int n;
	unsigned long outlen;
	int rawcpl;
	rawcpl = cpl * 3 / 4;
	dropbear_assert((unsigned int)cpl < sizeof(out));

    while (datalen > 0) {
		n = (datalen < rawcpl ? datalen : rawcpl);
		outlen = sizeof(out);
		base64_encode(data, n, out, &outlen);
		data += n;
		datalen -= n;
		fwrite(out, 1, outlen, fp);
		fputc('\n', fp);
    }
}
