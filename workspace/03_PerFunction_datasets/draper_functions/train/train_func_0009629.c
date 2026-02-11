cpl_property_set_long_long(cpl_property *self, long long value)
{

    cxint status = 0;


    if (self == NULL) {
        return cpl_error_set_(CPL_ERROR_NULL_INPUT);
    }

    cx_assert(self->value != NULL);

    status = _cpl_property_value_set(self->value, CPL_TYPE_LONG_LONG,
                                     1, (cxcptr)&value);

    if (status) {
        return cpl_error_set_(CPL_ERROR_TYPE_MISMATCH);
    }

    return CPL_ERROR_NONE;

}
