tinf_decode_trees(TINF_DATA *d, TINF_TREE *lt, TINF_TREE *dt)
{
   TINF_TREE code_tree;
   unsigned char lengths[288+32];
   unsigned int hlit, hdist, hclen;
   unsigned int i, num, length;


   hlit = tinf_read_bits(d, 5, 257);


   hdist = tinf_read_bits(d, 5, 1);


   hclen = tinf_read_bits(d, 4, 4);

   for (i = 0; i < 19; ++i) lengths[i] = 0;


   for (i = 0; i < hclen; ++i)
   {

      unsigned int clen = tinf_read_bits(d, 3, 0);

      lengths[clcidx[i]] = clen;
   }


   tinf_build_tree(&code_tree, lengths, 19);


   for (num = 0; num < hlit + hdist; )
   {
      int sym = tinf_decode_symbol(d, &code_tree);

      switch (sym)
      {
      case 16:

         {
            unsigned char prev = lengths[num - 1];
            length = tinf_read_bits(d, 2, 3);
            if((num + length) > (288+32)) return TINF_DATA_ERROR;
            for (; length; --length)
            {
               lengths[num++] = prev;
            }
         }
         break;
      case 17:

         length = tinf_read_bits(d, 3, 3);
         if((num + length) > (288+32)) return TINF_DATA_ERROR;
         for (; length; --length)
         {
            lengths[num++] = 0;
         }
         break;
      case 18:

         length = tinf_read_bits(d, 7, 11);
         if((num + length) > (288+32)) return TINF_DATA_ERROR;
         for (; length; --length)
         {
            lengths[num++] = 0;
         }
         break;
      default:

         if((num + 1) > (288+32)) return TINF_DATA_ERROR;
         lengths[num++] = sym;
         break;
      }
   }


   tinf_build_tree(lt, lengths, hlit);
   tinf_build_tree(dt, lengths + hlit, hdist);
   return TINF_OK;
}
