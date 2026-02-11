datetime_to_char_body(TmToChar *tmtc, text *fmt, bool is_interval)
{
	FormatNode *format;
	char	   *fmt_str,
			   *result;
	bool		incache;
	int			fmt_len = VARSIZE(fmt) - VARHDRSZ;
	int			reslen;
	text	   *res;


	fmt_str = (char *) palloc(fmt_len + 1);
	memcpy(fmt_str, VARDATA(fmt), fmt_len);
	*(fmt_str + fmt_len) = '\0';


	result = palloc((fmt_len * DCH_MAX_ITEM_SIZ) + 1);
	*result = '\0';


	if (fmt_len > DCH_CACHE_SIZE)
	{
		format = (FormatNode *) palloc((fmt_len + 1) * sizeof(FormatNode));
		incache = FALSE;

		parse_format(format, fmt_str, DCH_keywords,
					 DCH_suff, DCH_index, DCH_TYPE, NULL);

		(format + fmt_len)->type = NODE_TYPE_END;
	}
	else
	{


		DCHCacheEntry *ent;

		incache = TRUE;

		if ((ent = DCH_cache_search(fmt_str)) == NULL)
		{
			ent = DCH_cache_getnew(fmt_str);


			parse_format(ent->format, fmt_str, DCH_keywords,
						 DCH_suff, DCH_index, DCH_TYPE, NULL);

			(ent->format + fmt_len)->type = NODE_TYPE_END;

#ifdef DEBUG_TO_FROM_CHAR


#endif
		}
		format = ent->format;
	}


	DCH_processor(format, result, true, is_interval, (void *) tmtc);

	if (!incache)
		pfree(format);

	pfree(fmt_str);


	reslen = strlen(result);
	res = (text *) palloc(reslen + VARHDRSZ);
	memcpy(VARDATA(res), result, reslen);
	SET_VARSIZE(res, reslen + VARHDRSZ);

	pfree(result);
	return res;
}
