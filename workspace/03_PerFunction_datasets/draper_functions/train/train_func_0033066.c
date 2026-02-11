canon_exposureinfo(FILE *inptr,unsigned short byteorder,char *tagprefix,
                            unsigned long offset,unsigned long dirlength,int indent,
                            struct image_summary *summary_entry)
{
    unsigned long count,value;
    unsigned long end_offset;
    float fvalue;
    int i;
    int chpr = 0;

    if(PRINT_SECTION)
    {
        chpr += printf(" length %lu",dirlength);
        chpr = newline(chpr);
    }


    end_offset = offset + dirlength;
    count = (dirlength / sizeof(unsigned long));

    for(i = 0; i < count; ++i)
    {
        value = read_ulong(inptr,byteorder,offset);
        print_tag_address(ENTRY,offset,indent,"@");
        if((PRINT_ENTRY))
        {
            if((PRINT_TAGINFO))
                chpr += printf("%s",tagprefix);
        }
        offset += 4;
        switch(i)
        {
            case 0:
                fvalue = to_float(value);
                if((PRINT_TAGINFO))
                    chpr += printf(".%02d_%-22.22s",i,"ExposureCompensation");
                if((PRINT_VALUE))
                    chpr += printf(" = %f",fvalue);
                break;
            case 1:
                fvalue = to_float(value);
                if((PRINT_TAGINFO))
                    chpr += printf(".%02d_%-22.22s",i,"Tv");
                if((PRINT_VALUE))
                    chpr += printf(" = %f",fvalue);
                break;
            case 2:
                fvalue = to_float(value);
                if((PRINT_TAGINFO))
                    chpr += printf(".%02d_%-22.22s",i,"Av");
                if((PRINT_VALUE))
                    chpr += printf(" = %f",fvalue);
                break;
            default:
                fvalue = to_float(value);
                if((PRINT_TAGINFO))
                    chpr += printf(".%02d_%-22.22s",i,"Undefined");
                if((PRINT_VALUE))
                    chpr += printf(" = %f",fvalue);
                break;
        }
        chpr = newline(chpr);
    }
    setcharsprinted(chpr);
    return(end_offset);
}
