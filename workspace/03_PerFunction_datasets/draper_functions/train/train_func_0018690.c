print_mrw_header(struct fileheader *fileheader,unsigned long section_id)
{
    struct mrw_header mrwheader;
    int status = -1;
    int chpr = 0;

    if(Print_options & section_id)
    {
        if(fileheader && (fileheader->probe_magic == PROBE_MRWMAGIC))
        {
            mrwheader = fileheader->mrw_header;
            if(mrwheader.mrw_magic == PROBE_MRWMAGIC)
            {
                chpr += printf("MRW magic %#lx, length %u, offset to image data %lu",
                                            mrwheader.mrw_magic,8,mrwheader.mrw_dataoffset + 8);
                chpr = newline(chpr);
                status = 0;
            }
            else
                chpr += printf(" MRW HEADER MAGIC BAD");
        }
        else
            chpr += printf(" NOT AN MRW HEADER");
    }
    chpr = newline(chpr);
    return(status);
}
