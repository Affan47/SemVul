MD5Final (private_md5_hasher_t *this, u_int8_t digest[16])
{
	u_int8_t bits[8];
	size_t index, padLen;


	Encode (bits, this->count, 8);


	index = (size_t)((this->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	MD5Update (this, PADDING, padLen);


	MD5Update (this, bits, 8);

	if (digest != NULL)
	{

		Encode (digest, this->state, 16);
	}
}
