cpl_propertylist_prepend_property(cpl_propertylist *self,
                                  const cpl_property *property)
{

    if((self == NULL) || (property == NULL)){
        return cpl_error_set_(CPL_ERROR_NULL_INPUT);
    }

    cx_deque_push_front(self->properties, cpl_property_duplicate(property));


    return CPL_ERROR_NONE;
}
