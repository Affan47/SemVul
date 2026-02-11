parse_pair(heim_dict_t dict, struct parse_ctx *ctx)
{
    heim_string_t key;
    heim_object_t value;

    if (white_spaces(ctx))
	return -1;

    if (*ctx->p == '}')
	return 0;

    key = parse_string(ctx);
    if (key == NULL)
	return -1;

    if (white_spaces(ctx))
	return -1;

    if (*ctx->p != ':') {
	heim_release(key);
	return -1;
    }

    ctx->p += 1;

    if (white_spaces(ctx)) {
	heim_release(key);
	return -1;
    }

    value = parse_value(ctx);
    if (value == NULL) {
	heim_release(key);
	return -1;
    }
    heim_dict_set_value(dict, key, value);
    heim_release(key);
    heim_release(value);

    if (white_spaces(ctx))
	return -1;

    if (*ctx->p == '}') {
	ctx->p++;
	return 0;
    } else if (*ctx->p == ',') {
	ctx->p++;
	return 1;
    }
    return -1;
}
