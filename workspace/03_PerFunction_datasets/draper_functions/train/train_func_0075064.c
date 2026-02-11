cpl_parameter_get_range_min_int(const cpl_parameter *self)
{


    if (!self) {
        cpl_error_set(cpl_func, CPL_ERROR_NULL_INPUT);
        return 0;
    }

    if (self->class != CPL_PARAMETER_CLASS_RANGE) {
        (void)cpl_error_set_message(cpl_func, CPL_ERROR_TYPE_MISMATCH, "%s of "
                                    "type %s", cpl_parameter_get_name(self),
                                    cpl_type_get_name(cpl_parameter_get_type
                                                      (self)));
        return 0;
    }

    cx_assert(self->data);

    if (((cpl_parameter_range *)self->data)->value.type != CPL_TYPE_INT) {
        (void)cpl_error_set_message(cpl_func, CPL_ERROR_TYPE_MISMATCH, "%s of "
                                    "type %s", cpl_parameter_get_name(self),
                                    cpl_type_get_name(cpl_parameter_get_type
                                                      (self)));
        return 0;
    }

    return ((cpl_parameter_range *)self->data)->min.i;

}
