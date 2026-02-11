bitzi_cache_add(bitzi_data_t *data, const xnode_t *root)
{
	struct bzdata bz;
	struct bzdata *bzo;

	g_assert(data != NULL);
	g_assert(data->sha1 != NULL);
	g_assert(NULL == data->ticket);

	bzo = get_bzdata(data->sha1);


	if (NULL == bzo) {
		bzo = &bz;
		ZERO(&bz);
		bzo->ctime = tm_time();
		gnet_stats_inc_general(GNR_BITZI_TICKETS_HELD);
	} else {
		if (data->expiry < bzo->etime) {
			g_message("%s: entry for %s already present and expires later",
				G_STRFUNC, sha1_to_string(data->sha1));
			return FALSE;
		}

		if (bzo->size != 0 && bzo->size != data->size) {
			g_warning("%s: entry for %s already present with filesize %s but "
				"new entry says %s, keeping old ticket",
				G_STRFUNC, sha1_to_string(data->sha1),
				filesize_to_string(bzo->size),
				filesize_to_string2(data->size));
			return FALSE;
		}
	}

	if (NULL == bzo->mime_type) {
		atom_str_change(&bzo->mime_type, data->mime_type);
	}
	if (NULL == bzo->mime_desc) {
		atom_str_change(&bzo->mime_desc, data->mime_desc);
	} else if (
		data->mime_desc != NULL &&
		strlen(bzo->mime_desc) < strlen(data->mime_desc)
	) {

		atom_str_change(&bzo->mime_desc, data->mime_desc);
	}


	HFREE_NULL(bzo->ticket);
	if (data->size != 0) {
		bzo->ticket = xfmt_tree_to_string_extended(root, XFMT_O_SINGLE_LINE,
			bitzi_prefixes, G_N_ELEMENTS(bitzi_prefixes), BITZI_RDF);
	}
	bzo->size = data->size;
	bzo->duration = data->duration;
	bzo->judgment = data->judgment;
	bzo->goodness = data->goodness;
	bzo->etime = data->expiry;

	dbmw_write(db_bzdata, data->sha1, bzo, sizeof *bzo);

	if (GNET_PROPERTY(bitzi_debug)) {
		g_debug("BITZI %s: %s %s ticket, filesize=%s, type=%s, desc=\"%s\", "
			"judgment=\"%s\", goodness=%g, duration=%s, expire=%s",
			G_STRFUNC, bzo->ctime == tm_time() ? "added" : "updated",
			sha1_to_string(data->sha1),
			filesize_to_string(bzo->size), bzo->mime_type,
			bzo->mime_desc, bitzi_judgment_to_string(bzo->judgment),
			bzo->goodness, short_time_ascii(bzo->duration),
			timestamp_to_string(bzo->etime));
		if (GNET_PROPERTY(bitzi_debug) > 5 && bzo->ticket != NULL) {
			g_debug("BITZI XML ticket:");
			dump_string(stderr, bzo->ticket, strlen(bzo->ticket), "");
		}
	}

	return TRUE;
}
