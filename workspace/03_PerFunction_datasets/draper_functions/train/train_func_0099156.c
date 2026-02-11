cpl_propertylist_prepend_long_long(cpl_propertylist *self, const char *name,
                                   long long value)
{


    cpl_property *property = NULL;


    if (self == NULL || name == NULL) {
        return cpl_error_set_(CPL_ERROR_NULL_INPUT);
    }

    property = cpl_property_new(name, CPL_TYPE_LONG_LONG);
    cx_assert(property != NULL);

    cpl_property_set_long_long(property, value);
    cx_deque_push_front(self->properties, property);

    return CPL_ERROR_NONE;

}
