print_private_entry(FILE *inptr,unsigned short byteorder,struct ifd_entry *entry_ptr,
                            unsigned long fileoffset_base, unsigned short subifd_ident,
                            struct image_summary *summary_entry, char *parent_name,
                            char *prefix,int make,int model,int indent)
{
    int value_is_offset = 0;
    unsigned long endoffset = 0UL;
    int chpr = 0;

    if((PRINT_ENTRY))
    {
        value_is_offset = is_offset(entry_ptr);
        if(value_is_offset == 0)
            value_is_offset = private_value_is_offset(make,subifd_ident,entry_ptr->tag);
        print_private_taginfo(entry_ptr,subifd_ident,parent_name,make,indent);
        if((entry_ptr->value_type == 0) || (entry_ptr->value_type > DOUBLE) ||
            ferror(inptr) || feof(inptr))
        {
            clearerr(inptr);
            printred("# INVALID ENTRY");
            endoffset = ftell(inptr);
        }
        else if(entry_ptr->count == 0)
        {
            if(PRINT_VALUE)
                chpr += printf(" EMPTY (value=%#lx)",entry_ptr->value);
            endoffset = ftell(inptr);
        }
        else if(value_is_offset)
        {
            if(value_is_offset > 0)
            {


                if(PRINT_BOTH_OFFSET)
                    chpr += printf("@%#lx=%lu",entry_ptr->value + fileoffset_base,
                            entry_ptr->value + fileoffset_base);
                else if(PRINT_HEX_OFFSET)
                    chpr += printf("@%#lx",entry_ptr->value + fileoffset_base);
                else if(PRINT_DEC_OFFSET)
                    chpr += printf("@%lu",entry_ptr->value + fileoffset_base);

                if(fileoffset_base && (PRINT_ENTRY_RELOFFSET))
                    chpr += printf(" (%lu) ",entry_ptr->value);
            }
            else if((value_is_offset < 0) && (PRINT_VALUE))
            {
                print_value(entry_ptr,PREFIX);
                interpret_pe_value(entry_ptr,subifd_ident,make,prefix);
            }


            if(!(PRINT_VALUE_AT_OFFSET))
            {
                setcharsprinted(chpr);
                chpr = 0;
                endoffset = print_offset_pe_value(inptr,byteorder,
                                            entry_ptr,fileoffset_base,
                                            subifd_ident,summary_entry,
                                            parent_name,"@",indent + MEDIUMINDENT,
                                            make,model,0);
            }
        }
        else if(PRINT_VALUE)
        {
            print_value(entry_ptr,PREFIX);
            interpret_pe_value(entry_ptr,subifd_ident,make,prefix);
        }
        chpr = newline(chpr);
    }
    return(endoffset);
}
