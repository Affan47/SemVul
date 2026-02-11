MD5Final (digest, context)
unsigned char digest[16];
MD5_CTX *context;
{
  unsigned char bits[8];
  unsigned int index, padLen;


  Encode (bits, context->count, 8);


  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  MD5Update (context, PADDING, padLen);


  MD5Update (context, bits, 8);

  if (digest != NULL)
  {

	  Encode (digest, context->state, 16);


	  MD5_memset ((POINTER)context, 0, sizeof (*context));
  }
}
