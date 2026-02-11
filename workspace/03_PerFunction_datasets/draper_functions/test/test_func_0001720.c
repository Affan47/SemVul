kmo_dfs_get_property_int(cpl_propertylist *header, const char *keyword)
{
    int         ret_val = INT_MIN;

    KMO_TRY
    {
        KMO_TRY_ASSURE((header != NULL) && (keyword != NULL),
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data provided!");

        KMO_TRY_ASSURE(cpl_propertylist_has(header, keyword) != 0,
                       CPL_ERROR_DATA_NOT_FOUND,
                       "Wrong property keyword: %s", keyword);

        KMO_TRY_ASSURE(cpl_propertylist_get_type(header, keyword) ==
                                                               CPL_TYPE_INT,
                       CPL_ERROR_INVALID_TYPE,
                       "Unexpected type for property %s: it should be integer",
                       keyword);

        KMO_TRY_EXIT_IF_ERROR(
            ret_val = cpl_propertylist_get_int(header, keyword));
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();

        ret_val = INT_MIN;
    }

    return ret_val;
}
