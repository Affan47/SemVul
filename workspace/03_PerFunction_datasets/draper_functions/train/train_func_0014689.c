es_lockSurface(sdl_data *sd, int len, char * buff)
{
   char *bp, *start;
   SDL_Surface * sptr;
   int sendlen, res;

   bp = buff;
   POPGLPTR(sptr, bp);
   if(sptr == NULL)
      error();
   res = SDL_LockSurface(sptr);
   bp = start = sdl_get_temp_buff(sd, 1);
   put8(bp, res);

   sendlen = bp - start;
   sdl_send(sd, sendlen);
}
