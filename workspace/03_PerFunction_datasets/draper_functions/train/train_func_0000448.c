clear()
    {
        if (reg)
            XDestroyRegion(reg);
        for (unsigned i = 0; i < 256; ++i)
            if (GCs[i])
                XFreeGC(display, GCs[i]);
    }
