output_euc_html_safe_string(property, string)
    Response_Property *property;
    const char *string;
{
    char encoded_string[MAX_STRING_LENGTH + 1];
    char *encoded_p;
    size_t encoded_length;
    const char *string_p;
    const char *entity;
    size_t entity_length;

    encoded_p = encoded_string;
    encoded_length = 0;

    for (string_p = string; *string_p != '\0'; string_p++) {


	if (MAX_STRING_LENGTH - MAX_ENTITY_NAME_LENGTH < encoded_length) {
	    *encoded_p = '\0';
	    output_string(property, encoded_string);
	    encoded_p = encoded_string;
	    encoded_length = 0;
	}

	if (0x21 <= *string_p && *string_p <= 0x7e)
	    entity = latin1_entity_name_table[*(unsigned char *)string_p];
	else
	    entity = NULL;

	if (entity != NULL) {
	    entity_length = strlen(entity);
	    *encoded_p++ = '&';
	    memcpy(encoded_p, entity, entity_length);
	    encoded_p += entity_length;
	    *encoded_p++ = ';';
	    encoded_length += entity_length + 2;
	} else {
	    *encoded_p++ = *string_p;
	    encoded_length++;
	}
    }

    if (0 < encoded_length) {
	*encoded_p = '\0';
	output_string(property, encoded_string);
    }
}
