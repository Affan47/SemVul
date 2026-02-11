write_old_procformatstring_type(FILE *file, int indent,
                                                    const type_t *type,
                                                    const attr_list_t *attrs,
                                                    int is_return, int is_interpreted)
{
    unsigned int size;

    int is_in = is_attr(attrs, ATTR_IN);
    int is_out = is_attr(attrs, ATTR_OUT);

    if (!is_in && !is_out) is_in = TRUE;

    if (type_get_type(type) == TYPE_BASIC ||
        type_get_type(type) == TYPE_ENUM)
    {
        unsigned char fc;

        if (is_return)
            print_file(file, indent, "0x53,    /* FC_RETURN_PARAM_BASETYPE */\n");
        else
            print_file(file, indent, "0x4e,    /* FC_IN_PARAM_BASETYPE */\n");

        if (type_get_type(type) == TYPE_ENUM)
        {
            fc = get_enum_fc(type);
        }
        else
        {
            fc = get_basic_fc_signed(type);

            if (fc == RPC_FC_BIND_PRIMITIVE)
                fc = RPC_FC_IGNORE;
        }

        print_file(file, indent, "0x%02x,    /* %s */\n",
                   fc, string_of_type(fc));
        size = 2;
    }
    else
    {
        unsigned short offset = type->typestring_offset;

        if (is_interpreted && is_array(type) &&
            type_array_is_decl_as_ptr(type) &&
            type->details.array.ptr_tfsoff)
            offset = type->details.array.ptr_tfsoff;

        if (is_return)
            print_file(file, indent, "0x52,    /* FC_RETURN_PARAM */\n");
        else if (is_in && is_out)
            print_file(file, indent, "0x50,    /* FC_IN_OUT_PARAM */\n");
        else if (is_out)
            print_file(file, indent, "0x51,    /* FC_OUT_PARAM */\n");
        else
            print_file(file, indent, "0x4d,    /* FC_IN_PARAM */\n");

        size = get_stack_size( type, attrs, NULL );
        print_file(file, indent, "0x%02x,\n", size / pointer_size );
        print_file(file, indent, "NdrFcShort(0x%x),	/* type offset = %u */\n", offset, offset);
        size = 4;
    }
    return size;
}
