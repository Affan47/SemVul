c_param_write(gs_c_param_list * plist, gs_param_name pkey, void *pvalue,
              gs_param_type type)
{
    unsigned top_level_sizeof = 0;
    unsigned second_level_sizeof = 0;
    gs_c_param *pparam = c_param_add(plist, pkey);

    if (pparam == 0)
        return_error(gs_error_VMerror);
    memcpy(&pparam->value, pvalue, gs_param_type_sizes[(int)type]);
    pparam->type = type;


    switch (type) {
            gs_param_string const *curr_string;
            gs_param_string const *end_string;

        case gs_param_type_string_array:
        case gs_param_type_name_array:

            curr_string = pparam->value.sa.data;
            end_string = curr_string + pparam->value.sa.size;
            for (; curr_string < end_string; ++curr_string)
                if (!curr_string->persistent)
                    second_level_sizeof += curr_string->size;


        case gs_param_type_string:
        case gs_param_type_name:
        case gs_param_type_int_array:
        case gs_param_type_float_array:
            if (!pparam->value.s.persistent) {
                byte *top_level_memory = NULL;

                top_level_sizeof =
                    pparam->value.s.size * gs_param_type_base_sizes[type];
                if (top_level_sizeof + second_level_sizeof > 0) {
                    top_level_memory =
                        gs_alloc_bytes_immovable(plist->memory,
                                     top_level_sizeof + second_level_sizeof,
                                             "c_param_write data");
                    if (top_level_memory == 0) {
                        gs_free_object(plist->memory, pparam, "c_param_write entry");
                        return_error(gs_error_VMerror);
                    }
                    memcpy(top_level_memory, pparam->value.s.data, top_level_sizeof);
                }
                pparam->value.s.data = top_level_memory;


                if (second_level_sizeof > 0) {
                    byte *second_level_memory =
                    top_level_memory + top_level_sizeof;

                    curr_string = pparam->value.sa.data;
                    end_string = curr_string + pparam->value.sa.size;
                    for (; curr_string < end_string; ++curr_string)
                        if (!curr_string->persistent) {
                            memcpy(second_level_memory,
                                   curr_string->data, curr_string->size);
                            ((gs_param_string *) curr_string)->data
                                = second_level_memory;
                            second_level_memory += curr_string->size;
                        }
                }
            }
            break;
        default:
            break;
    }

    plist->head = pparam;
    plist->count++;
    return 0;
}
