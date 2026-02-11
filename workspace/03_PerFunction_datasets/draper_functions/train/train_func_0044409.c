RsyncMD4FinalRsync (digest, context)
unsigned char digest[16];
RsyncMD4_CTX *context;
{
  unsigned char bits[8];
  unsigned int index, padLen;


  if ( context->rsyncMD4Bug ) {
      context->count[1] = 0;
  }
  RsyncMD4Encode (bits, context->count, 8);


  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  if ( !context->rsyncMD4Bug || index > 0 ) {
      padLen = (index < 56) ? (56 - index) : (120 - index);
      RsyncMD4Update (context, PADDING, padLen);


      RsyncMD4Update (context, bits, 8);

  }
  RsyncMD4Encode (digest, context->state, 16);


  RsyncMD4_memset ((POINTER)context, 0, sizeof (*context));
}
