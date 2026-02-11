QRinput_appendPaddingBit(BitStream *bstream, QRinput *input)
{
	int bits, maxbits, words, maxwords, i, ret;
	int padlen;

	bits = BitStream_size(bstream);
	maxwords = QRspec_getDataLength(input->version, input->level);
	maxbits = maxwords * 8;

	if(maxbits < bits) {
		errno = ERANGE;
		return -1;
	}
	if(maxbits == bits) {
		return 0;
	}

	if(maxbits - bits <= 4) {
		return BitStream_appendNum(bstream, maxbits - bits, 0);
	}

	words = (bits + 4 + 7) / 8;

	ret = BitStream_appendNum(bstream, words * 8 - bits, 0);
	if(ret < 0) return ret;

	padlen = maxwords - words;
	if(padlen > 0) {
		for(i=0; i<padlen; i++) {
			ret = BitStream_appendNum(bstream, 8, (i&1)?0x11:0xec);
			if(ret < 0) {
				return ret;
			}
		}
	}

	return 0;
}
