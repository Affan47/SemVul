send_cw_char(int c)
{
   unsigned char u;

   c = toupper(c);
   if (c < ' ' || c > 'Z')
      return;
   if (c == ' ')

      putcodeword( 0x0008 );
   else
   {
      u = cwtab[c - 33];
      while (u > 0)
      {
         if(u == 0x80)
         {


            putcodeword(0x0004);
         }
         else
            if (u & 0x80)
            {

               putcodeword(CODE_TONE_ON|0x000F);

            }
            else
            {

               putcodeword(CODE_TONE_ON|0x003);

            }

            putcodeword(0x0004);
            u = u << 1;
      }
   }
}
