cbf_set_tag_root (cbf_handle handle, const char* tagname,
                                            const char* tagroot)
{
    cbf_handle dictionary;

    unsigned int rownum;

    if (!handle || !tagname || !tagroot ) return CBF_ARGUMENT;

    cbf_failnez( cbf_require_dictionary(handle, &dictionary))

    if (!dictionary) return CBF_NOTFOUND;

    if ( cbf_find_tag(dictionary, "_item_aliases.alias_name")) {

        cbf_failnez( cbf_require_datablock(dictionary, "dictionary"))

        cbf_failnez( cbf_require_category(dictionary, "item_aliases"))

        cbf_failnez( cbf_require_column(dictionary, "alias_name"))
    }

    if (cbf_find_hashedvalue(dictionary, tagname, "alias_name",
              CBF_CASE_INSENSITIVE)) {

        cbf_failnez( cbf_set_hashedvalue(dictionary, tagname, "alias_name", -1))

    }

    cbf_failnez( cbf_row_number(dictionary, &rownum))

    cbf_failnez( cbf_set_hashedvalue(dictionary, tagroot, "root_name", rownum))

    return 0;

}
