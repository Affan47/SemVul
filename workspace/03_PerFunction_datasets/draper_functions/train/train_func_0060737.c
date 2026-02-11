_cpl_parameter_init(cpl_parameter *parameter, va_list *ap)
{

    cxint status;

    cx_assert(parameter != NULL);
    cx_assert(ap != NULL);

    switch (parameter->class) {
    case CPL_PARAMETER_CLASS_VALUE:
        status = _cpl_parameter_value_create(parameter, ap);
        break;

    case CPL_PARAMETER_CLASS_RANGE:
        status = _cpl_parameter_range_create(parameter, ap);
        break;

    case CPL_PARAMETER_CLASS_ENUM:
        status = _cpl_parameter_enum_create(parameter, ap);
        break;

    default:
        cpl_error_set(cpl_func, CPL_ERROR_INVALID_TYPE);
        status = -1;
        break;
    }

    if (status) {
        if (status == -1) {
            cx_warning("%s: parameter at %p has invalid class id %02x", cpl_func,
                       (const void*)parameter, parameter->class);
        }
        else {
            cx_warning("%s: parameter at %p has illegal combination of"
                       "class id (%02x) and type id (%02x)", cpl_func,
                       (const void*)parameter,
                       parameter->class, parameter->data->type);
        }
        return 1;
    }

    return 0;

}
