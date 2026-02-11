print_type(h5tools_str_t *buffer, hid_t type, int ind)
{
    H5T_class_t  data_class = H5Tget_class(type);


    if (type<0) {
        h5tools_str_append(buffer,"<ERROR>");
        return;
    }


    if(H5Tcommitted(type)) {
        H5O_info_t  oi;

        if(H5Oget_info(type, &oi) >= 0)
            h5tools_str_append(buffer,"shared-%lu:"H5_PRINTF_HADDR_FMT" ",
                    oi.fileno, oi.addr);
        else
            h5tools_str_append(buffer,"shared ");
    }


    if((!simple_output_g && print_native_type(buffer, type, ind)) ||
            print_ieee_type(buffer, type, ind) ||
            print_int_type(buffer, type, ind) ||
            print_float_type(buffer, type, ind) ||
            print_cmpd_type(buffer, type, ind) ||
            print_enum_type(buffer, type, ind) ||
            print_string_type(buffer, type, ind) ||
            print_reference_type(buffer, type, ind) ||
            print_vlen_type(buffer, type, ind) ||
            print_array_type(buffer, type, ind) ||
            print_opaque_type(buffer, type, ind) ||
            print_bitfield_type(buffer, type, ind))
        return;


    h5tools_str_append(buffer,"%lu-byte class-%u unknown",
            (unsigned long)H5Tget_size(type), (unsigned)data_class);
}
