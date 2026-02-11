subarray(unsigned adr, unsigned wid) const
{
      const unsigned BIT2_PER_WORD = 8*sizeof(unsigned long);
      unsigned awid = (wid + BIT2_PER_WORD - 1) / (BIT2_PER_WORD);
      unsigned long*val = new unsigned long[awid];

      for (unsigned idx = 0 ;  idx < awid ;  idx += 1)
	    val[idx] = 0;

      if (size_ <= BITS_PER_WORD) {


	    unsigned long atmp = abits_val_ >> adr;
	    unsigned long btmp = bbits_val_ >> adr;
	    if (wid < BIT2_PER_WORD) {
		  atmp &= (1UL << wid) - 1;
		  btmp &= (1UL << wid) - 1;
	    }
	    if (btmp) goto x_out;

	    val[0] = atmp;

      } else {

	    unsigned val_ptr = 0;
	    unsigned val_off = 0;


	    while (wid > 0) {
		  unsigned long atmp = abits_ptr_[adr/BITS_PER_WORD];
		  unsigned long btmp = bbits_ptr_[adr/BITS_PER_WORD];
		  unsigned long off = adr%BITS_PER_WORD;
		  atmp >>= off;
		  btmp >>= off;

		  unsigned long trans = BITS_PER_WORD - off;
		  if (trans > (BIT2_PER_WORD - val_off))
			trans = BIT2_PER_WORD - val_off;
		  if (wid < trans)
			trans = wid;
		  if (trans < BIT2_PER_WORD) {
			atmp &= (1UL << trans) - 1;
			btmp &= (1UL << trans) - 1;
		  }
		  if (btmp) goto x_out;

		  val[val_ptr] |= atmp << val_off;
		  adr += trans;
		  wid -= trans;
		  val_off += trans;
		  if (val_off == BIT2_PER_WORD) {
			val_ptr += 1;
			val_off = 0;
		  }
	    }
      }

      return val;

 x_out:
      delete[]val;
      return 0;
}
