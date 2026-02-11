squares_effect(SDL_Surface * s, SDL_Surface * img)
{
        int bpp = img->format->BytesPerPixel;
        const int squares_size = 32;

        int still_moving = 1;

        for (i=0; still_moving; i++) {
                int k = 0;

                synchro_before(s);

                still_moving = 0;
                for (j=i; j>=0; j--) {
                        if (fillrect(j, k, s ,img, bpp, squares_size))
                                still_moving = 1;
                        k++;
                }

                synchro_after(s);
        }
}
