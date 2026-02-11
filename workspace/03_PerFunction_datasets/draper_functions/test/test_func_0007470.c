addOverlay(const char *filename,
               unsigned long xpos,
               unsigned long ypos,
               Uint16 *pixel,
               unsigned long width,
               unsigned long height,
               unsigned int gray)
{
    if ((filename != NULL) && (pixel != NULL))
    {
#ifdef HAVE_IOS_NOCREATE
        STD_NAMESPACE ifstream input(filename, STD_NAMESPACE ios::in | STD_NAMESPACE ios::nocreate);
#else
        STD_NAMESPACE ifstream input(filename);
#endif
        if (input)
        {
            char c;
            unsigned int xsize, ysize;
            if (input.get(c) && (c == 'P') && input.get(c) && (c == '1'))
            {

                input >> xsize;
                input >> ysize;
                if ((xpos + xsize <= width) && (ypos + ysize <= height))
                {
                    unsigned int value;
                    Uint16 *p = pixel + (ypos * width) + xpos;
                    for (unsigned long ys = 0; ys < ysize; ys++)
                    {
                        for (unsigned long xs = 0; xs < xsize; xs++)
                        {
                            while (input.get(c) && !isdigit(OFstatic_cast(unsigned char, c)));
                            input.putback(c);
                            input >> value;
                            if (value)
                                *p = gray;
                            p++;
                        }
                        p += (width - xsize);
                    }
                    return 1;
                } else
                    OFLOG_ERROR(dcmpsprtLogger, "invalid position for overlay PBM file '" << filename);
            } else
                OFLOG_ERROR(dcmpsprtLogger, "overlay PBM file '" << filename << "' has no magic number P1");
        } else
            OFLOG_ERROR(dcmpsprtLogger, "can't open overlay PBM file '" << filename << "'");
    }
    return 0;
}
