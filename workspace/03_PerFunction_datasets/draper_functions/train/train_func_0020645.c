fadeout (void)


{
   int n;

   if (SDL_MUSTLOCK(virtue)) SDL_LockSurface(virtue);

   for (n = 0; n < HEIGHT; n += 2)
   {
      line(virtue, 0, n, WIDTH - 1, n, 0, 0, 0);
      if (n % 10 == 0)
      {
         if (SDL_MUSTLOCK(virtue)) SDL_UnlockSurface(virtue);
         SDL_UpdateRect(virtue, 0, 0, 0, 0);
         SDL_Delay(5);
         manageevents();
         if (keymap.escape)
         {
            return;
         }
         if (SDL_MUSTLOCK(virtue)) SDL_LockSurface(virtue);
      }
   }

   for (n = HEIGHT - 1; n > 0; n -= 2)
   {
      line(virtue, 0, n, WIDTH - 1, n, 0, 0, 0);
      if ((n + 1) % 10 == 0)
      {
         if (SDL_MUSTLOCK(virtue)) SDL_UnlockSurface(virtue);
         SDL_UpdateRect(virtue, 0, 0, 0, 0);
         SDL_Delay(5);
         manageevents();
         if (keymap.escape)
         {
            return;
         }
         if (SDL_MUSTLOCK(virtue)) SDL_LockSurface(virtue);
      }
   }

   if (SDL_MUSTLOCK(virtue)) SDL_UnlockSurface(virtue);

   SDL_UpdateRect(virtue, 0, 0, 0, 0);
   return;
}
