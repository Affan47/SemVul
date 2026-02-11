stc_iswhite(stcolor_device *sd, int prt_pixels,byte *ext_data)
{
   long  b2do = (prt_pixels*sd->color_info.depth+7)>>3;
   int   bcmp = 4 * countof(sd->stc.white_run);
   byte *wht  = (byte *) sd->stc.white_run;

   while(b2do >= bcmp) {
      if(memcmp(ext_data,wht,bcmp)) break;
      ext_data += bcmp;
      b2do     -= bcmp;
   }

   if((b2do > 0) && (b2do < bcmp))
      b2do  = memcmp(ext_data,sd->stc.white_end,b2do);

   return b2do ? false : true;
}
