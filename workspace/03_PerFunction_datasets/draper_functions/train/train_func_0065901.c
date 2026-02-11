GMT_grd_init (struct GRD_HEADER *header, int argc, char **argv, GMT_LONG update)
{


	GMT_LONG i, len;

	if (update)
		memset ((void *)header->command, 0, (size_t)GRD_COMMAND_LEN);
	else {
		memset ((void *)header, 0, (size_t)sizeof(struct GRD_HEADER));


		header->z_scale_factor		= 1.0;
		header->type			= -1;
		header->y_order			= 1;
		header->z_id			= -1;
		header->z_min			= GMT_d_NaN;
		header->z_max			= GMT_d_NaN;
		header->nan_value		= GMT_d_NaN;
		strcpy (header->x_units, "x");
		strcpy (header->y_units, "y");
		strcpy (header->z_units, "z");
		for (i = 0; i < 3; i++) header->t_index[i] = -1;
	}


	if (argc > 0) {
		strcpy (header->command, argv[0]);
		len = strlen (header->command);
		for (i = 1; len < GRD_COMMAND_LEN && i < argc; i++) {
			len += strlen (argv[i]) + 1;
			if (len > GRD_COMMAND_LEN) continue;
			strcat (header->command, " ");
			strcat (header->command, argv[i]);
		}
		header->command[len] = 0;
	}
}
