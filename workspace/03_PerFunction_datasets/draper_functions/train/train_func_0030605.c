setNumBands( unsigned int bands )
    {
        VIGRA_IMPEX_FINALIZED(pimpl->finalized);
        if (bands != 3) {
            vigra_fail("HDREncoder: can only save 3 channel images");
        }
        pimpl->samples_per_pixel = 3;
    }
