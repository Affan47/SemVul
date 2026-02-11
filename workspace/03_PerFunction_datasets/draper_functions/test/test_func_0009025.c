print_taginfo(struct ifd_entry *entry_ptr,char *parent_name,
                    int indent,int ifdtype,int ifdnum,int subifdnum)
{
    char *nameoftag;
    char *nameof_value_type;
    int tagwidth = TAGWIDTH;
    int chpr = 0;

    if(entry_ptr && (PRINT_ENTRY))
    {
        if(PRINT_BOTH_TAGNO)
            chpr += printf("<%#06x=%5u> ",entry_ptr->tag & 0xffff,entry_ptr->tag & 0xffff);
        else if(PRINT_DEC_TAGNO)
            chpr += printf("<%5u> ",entry_ptr->tag & 0xffff);
        else if(PRINT_HEX_TAGNO)
            chpr += printf("<%#06x> ",entry_ptr->tag & 0xffff);
        if((PRINT_TAGNAME))
        {
            switch(ifdtype)
            {
                case GPS_IFD:
                    nameoftag = gps_tagname(entry_ptr->tag);
                    break;
                case INTEROP_IFD:
                    nameoftag = interop_tagname(entry_ptr->tag);
                    break;
                case EXIF_IFD:
                case TIFF_IFD:
                case TIFF_SUBIFD:
                    nameoftag = tagname(entry_ptr->tag);
                    break;
                default:
                    nameoftag = tagname(entry_ptr->tag);
                    break;
            }
            if((PRINT_LONGNAMES))
                printf("%s.",parent_name);
            chpr += printf("%-*.*s",tagwidth,tagwidth,nameoftag ? nameoftag : "NULL");
        }
        if(PRINT_TYPE)
        {
            nameof_value_type = value_type_name(entry_ptr->value_type);
            chpr += printf(" [%-2u=%-9.9s %5lu] ",entry_ptr->value_type,
                    nameof_value_type,entry_ptr->count);
        }
        if(PRINT_VALUE)
            chpr += printf(" = ");
    }
    setcharsprinted(chpr);
}
