olympus1_interpret_offset_pe_value(FILE *inptr,unsigned short byteorder,
                    struct ifd_entry *entry_ptr,unsigned long fileoffset_base,
                    unsigned short subifd_ident)
{
    if(entry_ptr)
    {
        switch(subifd_ident)
        {
            case 0x2010:
                olympus2010_interpret_offset_value(inptr,byteorder,entry_ptr,fileoffset_base);
                break;
            case 0x2020:
                olympus2020_interpret_offset_value(inptr,byteorder,entry_ptr,fileoffset_base);
                break;
            case 0x2030:
                olympus2030_interpret_offset_value(inptr,byteorder,entry_ptr,fileoffset_base);
                break;
            case 0x2040:
                olympus2040_interpret_offset_value(inptr,byteorder,entry_ptr,fileoffset_base);
                break;
            case 0x2050:
                olympus2050_interpret_offset_value(inptr,byteorder,entry_ptr,fileoffset_base);
                break;
            default:
                break;
        }
    }
}
