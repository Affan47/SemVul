shrink_(SDL_Surface * dest, SDL_Surface * orig, int xpos, int ypos, SDL_Rect * orig_rect, int factor)
{
        int bpp = dest->format->BytesPerPixel;
        int rx = orig_rect->x / factor;
        int rw = orig_rect->w / factor;
        int ry = orig_rect->y / factor;
        int rh = orig_rect->h / factor;
        xpos -= rx;
        ypos -= ry;
        myLockSurface(orig);
        myLockSurface(dest);
        for (x=rx; x<rx+rw; x++) {
                for (y=ry; y<ry+rh; y++) {
                        if (!dest->format->palette) {

                                int r = 0;
                                int g = 0;
                                int b = 0;
                                int a = 0;
                                Uint8 r_, g_, b_ , a_;
                                for (i=0; i<factor; i++) {
                                        for (j=0; j<factor; j++) {
                                                SDL_GetRGBA(((Uint32 *)orig->pixels)[CLAMP(x*factor+i, 0, orig->w) +  CLAMP(y*factor+j, 0, orig->h) * orig->w],
                                                            orig->format, &r_, &g_, &b_, &a_);
                                                r += r_;
                                                g += g_;
                                                b += b_;
                                                a += a_;
                                        }
                                }
                                r /= factor*factor;
                                g /= factor*factor;
                                b /= factor*factor;
                                a /= factor*factor;
                                set_pixel(dest, CLAMP(xpos+x, 0, dest->w), CLAMP(ypos+y, 0, dest->h), (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
                        }


                }
        }
        myUnlockSurface(orig);
        myUnlockSurface(dest);
}
