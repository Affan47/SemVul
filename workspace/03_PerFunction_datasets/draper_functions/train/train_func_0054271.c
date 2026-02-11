cpl_propertylist_insert_after_double_complex(cpl_propertylist *self,
                                             const char *after,
                                             const char *name,
                                             double complex value)
{

    if (self == NULL || after == NULL || name == NULL) {
        return cpl_error_set_(CPL_ERROR_NULL_INPUT);
    }

    return _cpl_propertylist_insert(self, after, TRUE, name,
                                    CPL_TYPE_DOUBLE_COMPLEX,
                                    (cxcptr)&value)
        ? cpl_error_set_(CPL_ERROR_UNSPECIFIED) : CPL_ERROR_NONE;

}
