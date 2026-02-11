print_jp2box(FILE *inptr,struct jp2box *box,int indent)
{
    unsigned long boxlength = 0UL;
    int chpr = 0;

    if(box)
    {
        if(box->boxlength == 0UL)
            box->boxlength = get_filesize(inptr) - box->boxoffset;
        else
            boxlength = box->boxlength;
        if(PRINT_SECTION)
        {
            print_tag_address(SECTION,box->boxoffset,indent,"@");
            print_jp2type(box->tbox,0);
            chpr += printf(" <%#lx>",box->tbox);
            chpr += printf(" length %lu",boxlength);

            if(box->boxlength == 0UL)
                chpr += printf(" (0)");
            chpr += printf(" data offset %lu",box->dataoffset);
        }
    }
    chpr = newline(chpr);
}
