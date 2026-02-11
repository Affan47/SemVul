print_imagesize(struct image_summary *entry)
{
    int chpr = 0;
    char *maybeshort = NULLSTRING;

    if(entry)
    {
        if(entry->imagesubformat & IMGSUBFMT_JPEG_EARLY_EOI)
            maybeshort = "<= ";
        chpr += printf(" image [%ldx%ld",entry->pixel_width,entry->pixel_height);
        if(entry->subfiletype == PRIMARY_TYPE)
        {
            if((entry->primary_width > entry->pixel_width) ||
                       (entry->primary_height > entry->pixel_height))
            {
                chpr += printf("<=%ldx%ld",entry->primary_width,entry->primary_height);
            }
        }
        chpr += printf("] length %s%lu",maybeshort,entry->length);
    }
    setcharsprinted(chpr);
}
