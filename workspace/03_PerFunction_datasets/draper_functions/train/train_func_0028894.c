add_toptext(int ID, int px, int py, cchar *text, cchar *font)
{
   if (Ntoptext == maxtoptext) {
      printf("maxtoptext exceeded \n");
      return;
   }

   int ii = Ntoptext++;
   toptext[ii].ID = ID;
   toptext[ii].px = px;
   toptext[ii].py = py;
   toptext[ii].text = text;
   toptext[ii].font = font;

   return;
}
