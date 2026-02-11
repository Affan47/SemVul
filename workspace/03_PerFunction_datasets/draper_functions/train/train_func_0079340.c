build_huffman_table(const unsigned char *bits, const unsigned char *vals, struct huffman_table *table)
{
  unsigned int i, j, code, code_size, val, nbits;
  unsigned char huffsize[HUFFMAN_BITS_SIZE+1], *hz;
  unsigned int huffcode[HUFFMAN_BITS_SIZE+1], *hc;


  hz = huffsize;
  for (i=1; i<=16; i++)
   {
     for (j=1; j<=bits[i]; j++)
       *hz++ = i;
   }
  *hz = 0;

  memset(table->lookup, 0xff, sizeof(table->lookup));
  for (i=0; i<(16-HUFFMAN_HASH_NBITS); i++)
    table->slowtable[i][0] = 0;


  code = 0;
  hc = huffcode;
  hz = huffsize;
  nbits = *hz;
  while (*hz)
   {
     while (*hz == nbits)
      {
	*hc++ = code++;
	hz++;
      }
     code <<= 1;
     nbits++;
   }


  for (i=0; huffsize[i]; i++)
   {
     val = vals[i];
     code = huffcode[i];
     code_size = huffsize[i];

     trace("val=%2.2x code=%8.8x codesize=%2.2d\n", val, code, code_size);

     table->code_size[val] = code_size;
     if (code_size <= HUFFMAN_HASH_NBITS)
      {


	int repeat = 1UL<<(HUFFMAN_HASH_NBITS - code_size);
	code <<= HUFFMAN_HASH_NBITS - code_size;
	while ( repeat-- )
	  table->lookup[code++] = val;

      }
     else
      {

	uint16_t *slowtable = table->slowtable[code_size-HUFFMAN_HASH_NBITS-1];
	while(slowtable[0])
	  slowtable+=2;
	slowtable[0] = code;
	slowtable[1] = val;
	slowtable[2] = 0;

      }

   }
}
