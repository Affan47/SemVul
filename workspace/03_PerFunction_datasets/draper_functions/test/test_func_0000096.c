es_mapRGB(sdl_data *sd, int len, char *buff)
{
   char *bp, *start;
   int sendlen;
   SDL_Surface * sptr;
   Uint32 res;
   Uint8 r,g,b;

   bp = buff;
   POPGLPTR(sptr, bp);
   r = get8(bp);
   g = get8(bp);
   b = get8(bp);
   if(sptr == NULL  || sptr->format == NULL)
      error();
   res = SDL_MapRGB(sptr->format, r,g,b);

   bp = start = sdl_get_temp_buff(sd, 4);
   put32be(bp, res);
   sendlen = bp - start;
   sdl_send(sd, sendlen);
}
