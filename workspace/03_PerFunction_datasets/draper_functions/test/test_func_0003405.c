flip()
{
   static Uint32 ticks = 0;
   Uint32 cur_ticks = SDL_GetTicks();
   if (cur_ticks > ticks + 5 || cur_ticks < ticks) {
      SurfaceSDL *tmp = vga_front.get_buf();
      SDL_Surface *src = tmp->get_surface();
      ticks = cur_ticks;
      SDL_BlitSurface(src, NULL, front, NULL);
      SDL_Flip(front);
   }
}
