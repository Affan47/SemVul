print_volume_status(struct afp_volume * v,
	char * text,int * pos_p, int * len)
{
	struct afp_server * s = v->server;
	int pos = *pos_p;
	unsigned int fl = v->extra_flags;

	pos+=snprintf(text+pos,*len-pos,
		"    Volume %s, id %d, attribs 0x%x mounted: %s%s\n",
		v->volume_name_printable,v->volid,
		v->attributes,
		(v->mounted==AFP_VOLUME_MOUNTED) ? v->mountpoint:"No",
		((v->mounted==AFP_VOLUME_MOUNTED) && (volume_is_readonly(v))) ?
			" (read only)":"");

	if (v->mounted==AFP_VOLUME_MOUNTED) {
		pos+=snprintf(text+pos,*len-pos,
		"        did cache stats: %llu miss, %llu hit, %llu expired, %llu force removal\n        uid/gid mapping: %s (%d/%d)\n",
		v->did_cache_stats.misses, v->did_cache_stats.hits,
		v->did_cache_stats.expired,
		v->did_cache_stats.force_removed,
		get_mapping_name(v),
		s->server_uid,s->server_gid);
		pos+=snprintf(text+pos,*len-pos,
		"        Unix permissions: %s",
			(v->extra_flags&VOLUME_EXTRA_FLAGS_VOL_SUPPORTS_UNIX)?
				"Yes":"No");

		if (s->server_type==AFPFS_SERVER_TYPE_NETATALK) {
			pos+=snprintf(text+pos,*len-pos,
			", Netatalk permissions broken: ");

			if (fl&VOLUME_EXTRA_FLAGS_VOL_CHMOD_KNOWN)
				if (fl&VOLUME_EXTRA_FLAGS_VOL_CHMOD_BROKEN)
					pos+=snprintf(text+pos,*len-pos,
						"Yes\n");
				else
					pos+=snprintf(text+pos,*len-pos,
						"No\n");
			else
				pos+=snprintf(text+pos,*len-pos,
					"Unknown\n");
		}
	}
	*pos_p=pos;
}
