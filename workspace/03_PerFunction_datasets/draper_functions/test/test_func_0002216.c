drawquarterlightmap_sdl(int tl, int tr, int bl, int br,
                             int width, int height,
                             int startx, int starty, int endx, int endy,
                             int destx, int desty){
        int x,y;
        int top,bottom,val;
        for (x=startx;x<endx;x++){
                top= ((x*(tr-tl))/ width)+tl;
                bottom= ((x*(br-bl))/ width)+bl;
                for (y=starty;y<endy;y++){
                        val=((y*(bottom-top))/height)+top;
                        if (val>255)
                                val=255;
                        if (val<0)
                                val=0;

                        putpixel(lightmap, destx+x-startx, desty+y-starty,
                                SDL_MapRGBA(lightmap->format, 0, 0, 0, val));
                }
        }
}
