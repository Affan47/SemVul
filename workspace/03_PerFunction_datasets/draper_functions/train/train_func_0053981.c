kmo_get_pro_keyword_val(const cpl_propertylist *header, const char *par_name)
{
    int         found           = FALSE,
                ind             = 1;
    char        *keywordName    = NULL;
    const char  *val            = NULL,
                *keywordNameVal = NULL;

    KMO_TRY
    {
        KMO_TRY_ASSURE((header != NULL) ||
                       (par_name != NULL),
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data is provided!");


        KMO_TRY_EXIT_IF_NULL(
            keywordName = cpl_sprintf("ESO PRO REC1 PARAM%d NAME", ind));

        while (!found && cpl_propertylist_has(header, keywordName)) {
            KMO_TRY_EXIT_IF_NULL(
                keywordNameVal = cpl_propertylist_get_string(header, keywordName));

            if (strcmp(keywordNameVal, par_name) == 0) {
                found = TRUE;
                break;
            }

            cpl_free(keywordName); keywordName = NULL;

            ind++;
            KMO_TRY_EXIT_IF_NULL(
                keywordName = cpl_sprintf("ESO PRO REC1 PARAM%d NAME", ind));
        }

        if (found) {
            cpl_free(keywordName); keywordName = NULL;
            KMO_TRY_EXIT_IF_NULL(
                keywordName = cpl_sprintf("ESO PRO REC1 PARAM%d VALUE", ind));
            KMO_TRY_EXIT_IF_NULL(
                val = cpl_propertylist_get_string(header, keywordName));
            cpl_free(keywordName); keywordName = NULL;
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        val = NULL;
    }

    cpl_free(keywordName); keywordName = NULL;

    return val;
}
