coll_parse_sequence (xmmsv_coll_token_t *tokens, const char *field,
                     xmmsv_coll_t **ret)
{
	char *start, *end, *seq, *num;
	xmmsv_coll_t *coll, *parent;

	if (!tokens || (tokens->type != XMMS_COLLECTION_TOKEN_INTEGER &&
	                tokens->type != XMMS_COLLECTION_TOKEN_SEQUENCE)) {
		*ret = NULL;
		return tokens;
	}

	start = tokens->string;
	end = strchr (start, ',');


	if (end != NULL) {
		parent = xmmsv_coll_new (XMMS_COLLECTION_TYPE_UNION);
	} else {
		parent = NULL;
		end = start + strlen (start);
	}

	while (1) {
		seq = strchr (start, '-');


		if (seq != NULL && seq < end) {
			int len_from, len_to;
			xmmsv_coll_t *coll_from, *coll_to;
			char *buf;

			len_from = seq - start;
			len_to = end - seq - 1;

			if (len_from > 0) {
				buf = string_substr (start, seq);
				num = string_intadd (buf, -1);
				coll_from = xmmsv_coll_new (XMMS_COLLECTION_TYPE_GREATER);
				xmmsv_coll_attribute_set (coll_from, "field", field);
				xmmsv_coll_attribute_set (coll_from, "value", num);
				coll_append_universe (coll_from);
				free (buf);
				free (num);
			} else {
				coll_from = xmmsv_coll_universe ();
			}

			if (len_to > 0) {
				buf = string_substr (seq + 1, end);
				num = string_intadd (buf, 1);
				coll_to = xmmsv_coll_new (XMMS_COLLECTION_TYPE_SMALLER);
				xmmsv_coll_attribute_set (coll_to, "field", field);
				xmmsv_coll_attribute_set (coll_to, "value", num);
				xmmsv_coll_add_operand (coll_to, coll_from);
				xmmsv_coll_unref (coll_from);
				free (buf);
				free (num);
			} else {
				coll_to = coll_from;
			}

			coll = coll_to;


		} else {
			num = string_substr (start, end);
			coll = xmmsv_coll_new (XMMS_COLLECTION_TYPE_EQUALS);
			xmmsv_coll_attribute_set (coll, "field", field);
			xmmsv_coll_attribute_set (coll, "value", num);
			coll_append_universe (coll);
			free (num);
		}

		if (parent) {
			xmmsv_coll_add_operand (parent, coll);
		}


		if (*end == '\0') {
			break;
		}

		start = end + 1;
		end = strchr (start, ',');
		if (end == NULL) {
			end = start + strlen (start);
		}
	}

	if (parent) {
		coll = parent;
	}

	*ret = coll;
	return coll_next_token (tokens);
}
