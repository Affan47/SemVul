MD5Update (HL_MD5_CTX *context, unsigned char *input, unsigned int inputLen)
{
	  unsigned int i, index, partLen;


	  index = (unsigned int)((context->count[0] >> 3) & 0x3F);


	  if ( (context->count[0] += ((unsigned long int)inputLen << 3))
	       < ((unsigned long int)inputLen << 3))
		context->count[1]++;

	  context->count[1] += ((unsigned long int)inputLen >> 29);
	  partLen = 64 - index;


	  if (inputLen >= partLen)
	  {
		 MD5_memcpy ((POINTER)&context->buffer[index], (POINTER)input, partLen);
		 MD5Transform (context->state, context->buffer);

		 for (i = partLen; i + 63 < inputLen; i += 64)
		   MD5Transform (context->state, &input[i]);

		 index = 0;
	  }
	  else
	 	i = 0;


	  MD5_memcpy ((POINTER)&context->buffer[index],
	              (POINTER)&input[i],
		      inputLen-i);
}
