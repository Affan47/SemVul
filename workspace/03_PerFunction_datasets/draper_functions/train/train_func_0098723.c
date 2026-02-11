es_getKeyState(sdl_data *sd, int len,char *buff)
{
   Uint8 * keys;
   char *bp, *start;
   int length, sendlen, i;

   keys = SDL_GetKeyState(&length);
   bp = start = sdl_get_temp_buff(sd, length);
   for(i=0; i<length; i++)
      put8(bp, keys[i]);
   sendlen = bp - start;
   sdl_send(sd, sendlen);
}
