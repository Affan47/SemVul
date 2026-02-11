es_getGammaRamp(sdl_data *sd, int len, char * buff)
{
   char *bp, *start;
   int sendlen, res, i;
   Uint16 red[256], green[256],blue[256];
   res = SDL_GetGammaRamp(red,green,blue);
   bp = start = sdl_getbuff(sd, 4 + 256*2*3);
   put32be(bp, res);
   for(i=0; i<256; i++) {
      put16be(bp, red[i]);
   }
   for(i=0; i<256; i++) {
      put16be(bp, green[i]);
   }
   for(i=0; i<256; i++) {
      put16be(bp, blue[i]);
   }
   sendlen = bp - start;
   sdl_send(sd, sendlen);
}
