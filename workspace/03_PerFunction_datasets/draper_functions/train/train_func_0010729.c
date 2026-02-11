get_diphone_units(cst_utterance *utt)
{

    cst_relation *units;
    cst_item *s0, *s1, *u;
    float end0,end1;
    char diphone_name[22];
    cst_diphone_db *udb;
    int unit_entry;

    udb = val_diphone_db(utt_feat_val(utt,"diphone_db"));
    utt_set_feat(utt,"sts_list",sts_list_val(udb->sts));

    units = utt_relation_create(utt,"Unit");

    for (s0=relation_head(utt_relation(utt,"Segment"));
	 s0 && item_next(s0); s0=s1)
    {
	s1 = item_next(s0);
	cst_sprintf(diphone_name,
		    "%.10s-%.10s",
		    item_name(s0),
		    item_name(s1));

	unit_entry = get_diphone_entry(udb,diphone_name);

	if (unit_entry == -1)
	{
	    cst_errmsg("flite: udb failed to find entry for: %s\n",
		       diphone_name);
	    unit_entry = 0;
	}


	u = relation_append(units,NULL);
	item_add_daughter(s0,u);
	item_set_string(u,"name",diphone_name);
	end0 = item_feat_float(s0,"end");
	item_set_int(u,"target_end", (int)(end0*udb->sts->sample_rate));
	item_set_int(u,"unit_entry",unit_entry);
	item_set_int(u,"unit_start",udb->diphones[unit_entry].start_pm);
	item_set_int(u,"unit_end",
		     udb->diphones[unit_entry].start_pm +
		     udb->diphones[unit_entry].pb_pm);

	u = relation_append(units,NULL);
	item_add_daughter(s1,u);
	item_set_string(u,"name",diphone_name);
	end1 = item_feat_float(s1,"end");
	item_set_int(u,"target_end",(int)(((end0+end1)/2.0)*udb->sts->sample_rate));
	item_set_int(u,"unit_entry",unit_entry);
	item_set_int(u,"unit_start",
		     udb->diphones[unit_entry].start_pm +
		     udb->diphones[unit_entry].pb_pm);
	item_set_int(u,"unit_end",
		     udb->diphones[unit_entry].start_pm +
		     udb->diphones[unit_entry].pb_pm+
		     udb->diphones[unit_entry].end_pm);
    }

    return utt;
}
