cos_copy_element_value(cos_value_t *pcv, gs_memory_t *mem,
                       const cos_value_t *pvalue, bool copy)
{
    *pcv = *pvalue;
    if (pvalue->value_type == COS_VALUE_SCALAR && copy) {
        byte *value_data = gs_alloc_string(mem, pvalue->contents.chars.size,
                                           "cos_copy_element_value");

        if (value_data == 0)
            return_error(gs_error_VMerror);
        memcpy(value_data, pvalue->contents.chars.data,
               pvalue->contents.chars.size);
        pcv->contents.chars.data = value_data;
    }
    return 0;
}
