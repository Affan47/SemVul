process_jp2_xml(FILE *inptr,struct jp2box *box,int indent)
{
    unsigned long boxoffset,max_offset,dataoffset;
    unsigned long readsize;
    unsigned long boxlength,size;
    int chpr = 0;

    print_jp2box(inptr,box,indent);
    boxoffset = box->boxoffset;
    boxlength = box->boxlength;

    dataoffset = boxoffset + box->dataoffset;
    max_offset = box->boxoffset + box->boxlength;
    size = boxlength - 8;

    if((PRINT_SECTION))
    {
        print_tag_address(VALUE,dataoffset,indent + 10,"=");
        if((PRINT_VALUE))
        {
            if((inptr && (fseek(inptr,dataoffset,0)) != -1))
            {
                while(size > 0ULL)
                {
                    if(size > READSIZE)
                        readsize = READSIZE;
                    else
                        readsize = size;

                    setcharsprinted(chpr);
                    print_ascii(inptr,readsize,dataoffset);
                    dataoffset += readsize;
                    size -= readsize;
                }
            }
        }
        chpr = newline(chpr);
        print_tag_address(SECTION,dataoffset - 1,indent,"=");
        print_jp2type(box->tbox,1);
    }
    else if((LIST_MODE))
        chpr = list_jp2box(inptr,box,"JP2.",indent,1);
    chpr = newline(chpr);
    return(max_offset);
}
