unpack_cache_directive(ParseContext *context)
{
    Octstr *decoded = NULL;
    int ret;
    int val;

    ret = wsp_field_value(context, &val);
    if (parse_error(context) || ret == WSP_FIELD_VALUE_DATA) {
        warning(0, "Bad cache-directive");
        goto error;
    }

    if (ret == WSP_FIELD_VALUE_ENCODED) {
        decoded = wsp_cache_control_to_string(val);
        if (!decoded) {
            warning(0, "Bad cache-directive 0x%02x.", val);
            goto error;
        }
        octstr_append_char(decoded, '=');
        switch (val) {
        case WSP_CACHE_CONTROL_NO_CACHE:
        case WSP_CACHE_CONTROL_PRIVATE:
            if (parse_octets_left(context) == 0) {
                warning(0, "Too short cache-directive");
                goto error;
            }
            octstr_append_char(decoded, '"');
            do {
                Octstr *fieldname = unpack_field_name(context);
                if (!fieldname) {
                    warning(0, "Bad field name in cache directive");
                    goto error;
                }
                octstr_append(decoded, fieldname);
                octstr_destroy(fieldname);
                if (parse_octets_left(context) > 0) {
                    octstr_append_char(decoded, ',');
                    octstr_append_char(decoded, ' ');
                }
            } while (parse_octets_left(context) > 0 &&
                     !parse_error(context));
            octstr_append_char(decoded, '"');
            break;
        case WSP_CACHE_CONTROL_MAX_AGE:
        case WSP_CACHE_CONTROL_MAX_STALE:
        case WSP_CACHE_CONTROL_MIN_FRESH:
            {
                Octstr *seconds;
                seconds = wsp_unpack_integer_value(context);
                if (!seconds) {
                    warning(0, "Bad integer value in cache directive");
                    goto error;
                }
                octstr_append(decoded, seconds);
                octstr_destroy(seconds);
            }
            break;
        default:
            warning(0, "Unexpected value 0x%02x in cache directive.", val);
            break;
        }
    } else if (ret == WSP_FIELD_VALUE_NUL_STRING) {


        decoded = parse_get_nul_string(context);
        if (!decoded) {
            warning(0, "Format error in cache-control.");
            return NULL;
        }

        unpack_parameter(context, decoded);
    } else {
        panic(0, "Unknown field value type %d.", ret);
    }

    return decoded;

error:
    octstr_destroy(decoded);
    return NULL;
}
