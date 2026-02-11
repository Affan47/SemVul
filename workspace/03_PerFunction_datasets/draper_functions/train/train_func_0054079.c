cpl_propertylist_set_string(cpl_propertylist *self, const char *name,
                            const char *value)
{


    cpl_property *property;


    if (self == NULL || name == NULL || value == NULL) {
        return cpl_error_set_(CPL_ERROR_NULL_INPUT);
    }

    property = _cpl_propertylist_get(self, name);

    if (property == NULL) {
        return cpl_error_set_message_(CPL_ERROR_DATA_NOT_FOUND, "%s", name);
    }

    return cpl_property_set_string(property, value);

}
