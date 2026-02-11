cbf_set_tag_category (cbf_handle handle, const char* tagname,
                                            const char* categoryname)
{
    cbf_handle dictionary;

    char * tempcat;

    if (!handle || !tagname || !categoryname ) return CBF_ARGUMENT;

    cbf_failnez( cbf_require_dictionary(handle, &dictionary))

    if (!dictionary) return CBF_NOTFOUND;

    if ( cbf_find_tag(dictionary, "_item.name")) {

        cbf_failnez( cbf_require_datablock(dictionary, "dictionary"))

        cbf_failnez( cbf_require_category(dictionary, "item"))

        cbf_failnez( cbf_require_column(dictionary, "name"))
    }

    cbf_failnez( cbf_require_column(dictionary, "category_id"))

    cbf_failnez( cbf_rewind_row(dictionary))

    cbf_failnez( cbf_find_column(handle, "name"))

    while (!cbf_find_nextrow(dictionary,tagname)) {

        cbf_failnez( cbf_require_column(dictionary, "category_id"))

        if (!cbf_get_value(dictionary,(const char **)&tempcat)) {

          if (tempcat && !cbf_cistrcmp(tempcat,categoryname))return 0;

        }

	    if (!tempcat) return cbf_set_value(dictionary,categoryname);

        cbf_failnez( cbf_find_column(dictionary, "name"))

    }

    cbf_failnez( cbf_new_row(dictionary))

    cbf_failnez( cbf_set_value(dictionary,tagname))

    cbf_failnez( cbf_find_column(dictionary, "category_id"))

    return cbf_set_value(dictionary,categoryname);

}
