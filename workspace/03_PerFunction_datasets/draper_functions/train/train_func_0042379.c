free_bits_at_bottom (unsigned long a)


{

   if (!a)
      return sizeof (unsigned long) * 8;
   else if(((long) a) & 1l)
      return 0;
   else
      return 1 + free_bits_at_bottom ( a >> 1);
}
