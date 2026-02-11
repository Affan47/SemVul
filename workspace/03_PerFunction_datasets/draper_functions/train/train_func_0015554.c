remove_group_files(char group[INAME_LEN], char **rasters, int k)
{
    int m, n, skip;
    struct Ref ref;
    struct Ref ref_tmp;
    char *mapset;
    char tmp_name[INAME_LEN];
    char xname[GNAME_MAX], xmapset[GMAPSET_MAX];

    I_get_group_ref(group, &ref_tmp);
    I_init_group_ref(&ref);


    G_debug(3, "remove_group_files: ref_tmp.nfiles %d", ref_tmp.nfiles);

    for (m = 0; m < ref_tmp.nfiles; m++) {
	skip = 0;

	for (n = 0; n < k; n++) {
	    strcpy(tmp_name, rasters[n]);
	    mapset = G_mapset();


	    if (G__name_is_fully_qualified(rasters[n], xname, xmapset)) {
		strcpy(tmp_name, xname);
		mapset = xmapset;
	    }

	    G_debug(3, "tmp_name %s, ref_tmp.file[%d].name: %s", tmp_name, m,
		    ref_tmp.file[m].name);
	    if ((strcmp(tmp_name, ref_tmp.file[m].name) == 0) &&
		(strcmp(mapset, ref_tmp.file[m].mapset) == 0)) {
		G_message(_("Removing raster map <%s> from group"),
			  G_fully_qualified_name(tmp_name, mapset));
		skip = 1;
		break;
	    }
	}

	if (skip == 0) {
	    I_add_file_to_group_ref(ref_tmp.file[m].name,
				    ref_tmp.file[m].mapset, &ref);
	}
    }

    G_debug(1, "writing group REF");
    I_put_group_ref(group, &ref);

    if (ref.nfiles == ref_tmp.nfiles) {
	G_warning(_("No raster map removed"));
    }

    return 0;
}
