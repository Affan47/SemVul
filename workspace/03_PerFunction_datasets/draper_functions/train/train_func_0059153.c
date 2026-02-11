cpl_recipeconfig_get_outputs(const cpl_recipeconfig* self, const char* tag)
{

    static const cxchar* const _id = "cpl_recipeconfig_get_inputs";


    cxchar** tags = NULL;


    if (self == NULL) {
        cpl_error_set(_id, CPL_ERROR_NULL_INPUT);
        return NULL;
    }

    cx_assert(self->frames != NULL);

    if (tag == NULL) {
        cpl_error_set(_id, CPL_ERROR_NULL_INPUT);
        return NULL;
    }
    else {

        cpl_frameinfo* info = _cpl_recipeconfig_get_config(self, tag);

        if (info == NULL) {
            cpl_error_set(_id, CPL_ERROR_DATA_NOT_FOUND);
            return NULL;
        }

        tags = _cpl_recipeconfig_get_tags(info->oframes);

    }

    return tags;

}
