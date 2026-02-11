parse_attr_value(Octstr *attr_value, List *tokens,
			    wml_binary_t **wbxml, int charset, var_esc_t default_esc)
{
    int i, pos, wbxml_hex;
    wml_hash_t *temp = NULL;
    Octstr *cut_text = NULL;
    char *tmp;


    tmp = (char*) xmlGetCharEncodingName(charset);
    if (charset != XML_CHAR_ENCODING_UTF8 &&
        charset_convert(attr_value, "UTF-8",
                        tmp) != 0) {
        error(0, "Failed to convert XML attribute value from charset "
                 "<%s> to <%s>, will leave as is.", "UTF-8",
                 tmp ? tmp : "(undef)");
    }


    if (octstr_search_char(attr_value, '$', 0) >= 0) {
	if (parse_st_octet_string(attr_value, 0, default_esc, wbxml) != 0)
	    return -1;
    } else {

	for (i = 0; i < gwlist_len(tokens); i++) {
	    temp = gwlist_get(tokens, i);
	    pos = octstr_search(attr_value, temp->item, 0);
	    switch (pos) {
	    case -1:
		break;
	    case 0:
		wbxml_hex = temp->binary;
		output_st_char(wbxml_hex, wbxml);
		octstr_delete(attr_value, 0, octstr_len(temp->item));
		break;
	    default:


		gw_assert(pos <= octstr_len(attr_value));

		cut_text = octstr_copy(attr_value, 0, pos);
		if (parse_st_octet_string(cut_text, 0, default_esc, wbxml) != 0)
		    return -1;
		octstr_destroy(cut_text);

		wbxml_hex = temp->binary;
		output_st_char(wbxml_hex, wbxml);

		octstr_delete(attr_value, 0, pos + octstr_len(temp->item));
		break;
	    }
	}


	if ((int) octstr_len(attr_value) > 0) {
	    if (i < gwlist_len(tokens))
		parse_attr_value(attr_value, tokens, wbxml, charset, default_esc);
	    else
		if (parse_st_octet_string(attr_value, 0, default_esc, wbxml) != 0)
		    return -1;
	}
    }

    return 0;
}
