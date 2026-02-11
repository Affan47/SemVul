MGD77_Read_Data_Record_cdf (struct MGD77_CONTROL *F, struct MGD77_HEADER *H, double dvals[], char *tvals[])
{


	int i, c, id, n_val, n_txt;
	size_t start;

	for (i = n_val = n_txt = 0; i < F->n_out_columns; i++) {
		c  = F->order[i].set;
		id = F->order[i].item;
		H->info[c].bit_pattern |= MGD77_this_bit[id];
		start = (H->info[c].col[id].constant) ? 0 : F->rec_no;
		if (H->info[c].col[id].text) {
			MGD77_nc_status (nc_get_vara_schar (F->nc_id, H->info[c].col[id].var_id, &start, (size_t *)&H->info[c].col[id].text, (signed char *)tvals[n_txt++]));
		}
		else {
			MGD77_nc_status (nc_get_var1_double (F->nc_id, H->info[c].col[id].var_id, &start, &dvals[n_val]));
			MGD77_do_scale_offset_after_read (&dvals[n_val], (GMT_LONG)1, H->info[c].col[id].factor, H->info[c].col[id].offset, MGD77_NaN_val[H->info[c].col[id].type]);
			n_val++;
		}

	}
	return (MGD77_NO_ERROR);
}
