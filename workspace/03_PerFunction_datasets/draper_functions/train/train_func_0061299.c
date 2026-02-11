output_initialize_fp (cb_tree x, struct cb_field *f)
{
	output_prefix ();
	if (f->usage == CB_USAGE_FLOAT) {
		output ("{float temp = 0.0;");
	} else {
		output ("{double temp = 0.0;");
	}
	output (" memcpy (");
	output_data (x);
	output (", (char *)&temp, sizeof(temp));}\n");
}
