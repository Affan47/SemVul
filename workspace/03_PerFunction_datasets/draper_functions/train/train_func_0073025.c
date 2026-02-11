print_filetype(unsigned long magic,unsigned short marker)
{
    int status = -1;
    int chpr = 0;

    switch(magic)
    {
    case JPEG_SOI:
        chpr += printf("JPEG");
        status = 0;
        break;
    case ORF1_MAGIC:
        chpr += printf("ORF1");
        switch(marker)
        {
            case TIFF_INTEL:
                chpr += printf(":II");
                break;
            case TIFF_MOTOROLA:
                chpr += printf(":MM");
                break;
            default:
                break;
        }
        status = 0;
        break;
    case ORF2_MAGIC:
        chpr += printf("ORF2");
        switch(marker)
        {
            case TIFF_INTEL:
                chpr += printf(":II");
                break;
            case TIFF_MOTOROLA:
                chpr += printf(":MM");
                break;
            default:
                break;
        }
        status = 0;
        break;
    case TIFF_MAGIC:
        chpr += printf("TIFF");
        switch(marker)
        {
            case TIFF_INTEL:
                chpr += printf(":II");
                break;
            case TIFF_MOTOROLA:
                chpr += printf(":MM");
                break;
            default:
                break;
        }
        status = 0;
        break;
    case PROBE_CIFFMAGIC:
        chpr += printf("CIFF");
        switch(marker)
        {
            case TIFF_INTEL:
                chpr += printf(":II");
                break;
            case TIFF_MOTOROLA:
                chpr += printf(":MM");
                break;
            default:
                break;
        }
        status = 0;
        break;
    case PROBE_JP2MAGIC:
        chpr += printf("JP2");
        status = 0;
        break;
    case PROBE_MRWMAGIC:
        chpr += printf("MRW");
        status = 0;
        break;
    case PROBE_RAFMAGIC:
        chpr += printf("RAF");
        status = 0;
        break;
    case PROBE_X3FMAGIC:
        chpr += printf("X3F");
        status = 0;
        break;
    default:
        chpr += printf("UNKNOWN");
        break;
    }
    setcharsprinted(chpr);
    return(status);
}
