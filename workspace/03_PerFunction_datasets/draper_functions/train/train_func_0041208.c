flimage_free( FL_IMAGE * image )
{
    FL_IMAGE *im,
             *imnext;

    for ( im = image; im; im = imnext)
    {
        flimage_freemem( im );
        if ( im == image )
            flimage_close( im );
        imnext = im->next;
        fl_safe_free( im->infile );
        fl_safe_free( im->outfile );
        im->next = NULL;
        fl_free( im );
    }
}
