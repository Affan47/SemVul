cr_prop_list_allocate (void)
{
        CRPropList *result = NULL;

        result = g_try_malloc (sizeof (CRPropList));
        if (!result) {
                cr_utils_trace_info ("could not allocate CRPropList");
                return NULL;
        }
        memset (result, 0, sizeof (CRPropList));
        PRIVATE (result) = g_try_malloc (sizeof (CRPropListPriv));
        if (!result) {
                cr_utils_trace_info ("could not allocate CRPropListPriv");
                g_free (result);
                return NULL;
        }
        memset (PRIVATE (result), 0, sizeof (CRPropListPriv));
        return result;
}
