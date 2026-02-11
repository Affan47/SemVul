QRinput_appendPaddingBitMQR(BitStream *bstream, QRinput *input)
{
	int bits, maxbits, words, maxwords, i, ret, termbits;
	int padlen;

	bits = BitStream_size(bstream);
	maxbits = MQRspec_getDataLengthBit(input->version, input->level);
	maxwords = maxbits / 8;

	if(maxbits < bits) {
		errno = ERANGE;
		return -1;
	}
	if(maxbits == bits) {
		return 0;
	}

	termbits = input->version * 2 + 1;

	if(maxbits - bits <= termbits) {
		return BitStream_appendNum(bstream, maxbits - bits, 0);
	}

	bits += termbits;

	words = (bits + 7) / 8;
	if(maxbits - words * 8 > 0) {
		termbits += words * 8 - bits;
		if(words == maxwords) termbits += maxbits - words * 8;
	} else {
		termbits += words * 8 - bits;
	}
	ret = BitStream_appendNum(bstream, termbits, 0);
	if(ret < 0) return ret;

	padlen = maxwords - words;
	if(padlen > 0) {
		for(i=0; i<padlen; i++) {
			ret = BitStream_appendNum(bstream, 8, (i&1)?0x11:0xec);
			if(ret < 0) return ret;
		}
		termbits = maxbits - maxwords * 8;
		if(termbits > 0) {
			ret = BitStream_appendNum(bstream, termbits, 0);
			if(ret < 0) return ret;
		}
	}

	return 0;
}
