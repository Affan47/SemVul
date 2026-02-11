const_literal_to_rid(fs_query *q, rasqal_literal *l, fs_rid *attr)
{
    switch (l->type) {
	case RASQAL_LITERAL_URI: {
            char *uri = (char *)raptor_uri_as_string(l->value.uri);
            return fs_hash_uri(uri);
        }
        case RASQAL_LITERAL_XSD_STRING:
        case RASQAL_LITERAL_UDT:
	case RASQAL_LITERAL_STRING: {
            *attr = fs_c.empty;
            if (l->language) {
                char *langtag = g_utf8_strup(l->language, -1);
                *attr = fs_hash_literal(langtag, 0);
                g_free(langtag);
            } else if (l->datatype) {
                *attr = fs_hash_uri((char *)raptor_uri_as_string(l->datatype));
            }
	    return fs_hash_literal((char *)l->string, *attr);
        }
	case RASQAL_LITERAL_BOOLEAN:
            *attr = fs_c.xsd_boolean;
	    return fs_hash_literal(l->value.integer ?
			"true" : "false", *attr);
	case RASQAL_LITERAL_INTEGER:
        *attr = fs_c.xsd_integer;
	    return fs_hash_literal((char *)l->string, *attr);
	case RASQAL_LITERAL_INTEGER_SUBTYPE:
            *attr = fs_c.xsd_int;
	    return fs_hash_literal((char *)l->string, *attr);
	case RASQAL_LITERAL_DOUBLE:
            *attr = fs_c.xsd_double;
	    return fs_hash_literal((char *)l->string, *attr);
	case RASQAL_LITERAL_FLOAT:
            *attr = fs_c.xsd_float;
	    return fs_hash_literal((char *)l->string, *attr);
	case RASQAL_LITERAL_DECIMAL:
            *attr = fs_c.xsd_decimal;
	    return fs_hash_literal((char *)l->string, *attr);
	case RASQAL_LITERAL_DATETIME:
            *attr = fs_c.xsd_datetime;
	    return fs_hash_literal((char *)l->string, *attr);
	case RASQAL_LITERAL_VARIABLE:

            break;
	case RASQAL_LITERAL_BLANK:
	case RASQAL_LITERAL_PATTERN:
	case RASQAL_LITERAL_QNAME:
	case RASQAL_LITERAL_UNKNOWN:
	    fs_error(LOG_ERR, "error: found unhandled literal type %d", l->type);
            break;
    }
    *attr = FS_RID_NULL;

    return FS_RID_NULL;
}
