final_masking_message (hashblock delta_n, const hashblock delta_o,
		       const hashblock lstar, int j)
{
   hashblock l;

   switch (j)
      {
      case 1:

	 double_block (l, lstar);
	 xor_block (delta_n, delta_o, l);
	 break;

      case 2:

	 triple_block (l, lstar);
	 xor_block (delta_n, delta_o, l);
	 break;
      }
}
