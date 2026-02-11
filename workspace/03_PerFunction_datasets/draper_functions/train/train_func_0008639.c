leica1_offset_makervalue(FILE *inptr,unsigned short byteorder,
    struct ifd_entry *entry_ptr,unsigned long fileoffset_base,
    struct image_summary *summary_entry,char *parent_name,char *prefix,
    int indent,int make,int model,int at_offset)
{
    if(entry_ptr)
    {
        switch(entry_ptr->tag)
        {
            default:
                print_generic_offset_makervalue(inptr,byteorder,entry_ptr,
                                    fileoffset_base,parent_name,prefix,
                                    indent,make,model,at_offset);
                break;
        }
    }
}
