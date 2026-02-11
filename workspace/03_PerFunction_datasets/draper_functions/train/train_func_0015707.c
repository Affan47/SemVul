ncx_len_NC_attrV(nc_type type, size_t nelems)
{
        switch(type) {
        case NC_BYTE:
        case NC_CHAR:
                return ncx_len_char(nelems);
        case NC_SHORT:
                return ncx_len_short(nelems);
        case NC_INT:
                return ncx_len_int(nelems);
        case NC_FLOAT:
                return ncx_len_float(nelems);
        case NC_DOUBLE:
                return ncx_len_double(nelems);
        default:
                assert("ncx_len_NC_attr bad type" == 0);
        }
        return 0;
}
