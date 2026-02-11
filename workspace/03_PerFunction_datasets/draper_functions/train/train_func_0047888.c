pack_array(scanner_t *s, va_list *ap)
{
    json_t *array = json_array();
    next_token(s);

    while(s->token != ']') {
        json_t *value;

        if(!s->token) {
            set_error(s, "<format>", "Unexpected end of format string");
            goto error;
        }

        value = pack(s, ap);
        if(!value)
            goto error;

        if(json_array_append_new(array, value)) {
            set_error(s, "<internal>", "Unable to append to array");
            goto error;
        }

        next_token(s);
    }
    return array;

error:
    json_decref(array);
    return NULL;
}
