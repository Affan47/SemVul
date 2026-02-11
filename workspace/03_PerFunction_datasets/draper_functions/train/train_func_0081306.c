es_setClipRect(sdl_data *sd, int len, char *buff)
{
   char *bp;
   SDL_Surface * sptr;
   SDL_Rect rect;

   bp = buff;
   POPGLPTR(sptr, bp);
   rect.x = get16be(bp);
   rect.y = get16be(bp);
   rect.w = get16be(bp);
   rect.h = get16be(bp);
   if(sptr == NULL)
      error();
   SDL_SetClipRect(sptr, &rect);

}
