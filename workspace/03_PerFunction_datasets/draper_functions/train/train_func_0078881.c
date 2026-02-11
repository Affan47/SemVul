cpl_recipeconfig_set_tag(cpl_recipeconfig* self, const char* tag,
                         cpl_size min_count, cpl_size max_count)
{

    static const cxchar* const _id = "cpl_recipeconfig_set_tag";


    cxptr info = NULL;


    if ((self == NULL) || (tag == NULL)) {
        cpl_error_set(_id, CPL_ERROR_NULL_INPUT);
        return -1;
    }

    if (tag[0] == '\0') {
        cpl_error_set(_id, CPL_ERROR_ILLEGAL_INPUT);
        return -1;
    }


    cx_assert(self->frames != NULL);

    info = _cpl_recipeconfig_find(self->frames, tag);

    if (info != NULL) {
        cx_list_remove(self->frames, info);

        _cpl_frameinfo_delete(info);
        info = NULL;
    }

    info = _cpl_frameinfo_create(tag, min_count, max_count,
                                 cx_list_new(), cx_list_new());

    cx_list_push_back(self->frames, info);

    return 0;

}
