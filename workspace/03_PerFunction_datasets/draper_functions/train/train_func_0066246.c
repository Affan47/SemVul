fillrect(int i, int j, SDL_Surface * s, SDL_Surface * img,int bpp, const int squares_size)
        {
                int c, v;
                if (i >= XRES/squares_size || j >= YRES/squares_size)
                        return 0;
                v = i*squares_size*bpp + j*squares_size*img->pitch;
                for (c=0; c<squares_size; c++)
                        memcpy(s->pixels + v + c*img->pitch, img->pixels + v + c*img->pitch, squares_size*bpp);
                return 1;
        }
