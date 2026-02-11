I_EndRead(void)
{
    byte *screenloc = I_VideoBuffer
                    + (SCREENHEIGHT - LOADING_DISK_H) * SCREENWIDTH
                    + (SCREENWIDTH - LOADING_DISK_W);
    int y;

    if (!initialized || disk_image == NULL)
        return;


    for (y=0; y<LOADING_DISK_H; ++y)
    {
        memcpy(screenloc,
               saved_background + y * LOADING_DISK_W,
               LOADING_DISK_W);

        screenloc += SCREENWIDTH;
    }

    UpdateRect(SCREENWIDTH - LOADING_DISK_W, SCREENHEIGHT - LOADING_DISK_H,
               SCREENWIDTH, SCREENHEIGHT);
}
