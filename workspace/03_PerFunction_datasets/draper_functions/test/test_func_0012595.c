ScreenSwap(void)
{
    if(os_lock_bitmap())
    {
#ifndef IPHONE
        if(scaling)
        {
            scaling->Dest=screen->pixels;
            bitmapFastScale(scaling);
        }
        else if(screen->pitch==bitmap_width)
            memcpy(screen->pixels,main_bitmap,bitmap_width*bitmap_height);
        else
        {
            uint8_t *src = main_bitmap, *dest = screen->pixels;
            int i;

            for(i=bitmap_height;i;--i)
            {
                memcpy(dest,src,bitmap_width);
                src += bitmap_width;
                dest += screen->pitch;
            }
        }
#elif SCREEN_DEPTH == 16
        blitScreen16(screen->pixels);
#else
        blitScreen32(screen->pixels);
#endif
        os_unlock_bitmap();


        SDL_Flip(screen);
    }
}
