fn_build_float_array_forced(const ref * op, const char *kstr, bool required,
                     const float **pparray, gs_memory_t *mem)
{
    ref *par;
    int code;
    uint size;
    float *ptr;

    *pparray = 0;
    if (dict_find_string(op, kstr, &par) <= 0)
        return (required ? gs_note_error(e_rangecheck) : 0);

    if( r_is_array(par) )
        size = r_size(par);
    else if(r_type(par) == t_integer || r_type(par) == t_real)
        size = 1;
    else
        return_error(e_typecheck);
    ptr = (float *)gs_alloc_byte_array(mem, size, sizeof(float), kstr);

    if (ptr == 0)
        return_error(e_VMerror);
    if(r_is_array(par) )
        code = dict_float_array_check_param(mem, op, kstr,
                                            size, ptr, NULL,
                                            0, e_rangecheck);
    else {
        code = dict_float_param(op, kstr, 0., ptr);
        if( code == 0 )
            code = 1;
    }

    if (code < 0 ) {
        gs_free_object(mem, ptr, kstr);
        return code;
    }
    *pparray = ptr;
    return code;
}
