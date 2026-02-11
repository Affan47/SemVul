gp2ap020a00f_alter_opmode(struct gp2ap020a00f_data *data,
			enum gp2ap020a00f_opmode diff_mode, int add_sub)
{
	enum gp2ap020a00f_opmode new_mode;

	if (diff_mode != GP2AP020A00F_OPMODE_ALS &&
	    diff_mode != GP2AP020A00F_OPMODE_PS)
		return -EINVAL;

	if (add_sub == GP2AP020A00F_ADD_MODE) {
		if (data->cur_opmode == GP2AP020A00F_OPMODE_SHUTDOWN)
			new_mode =  diff_mode;
		else
			new_mode = GP2AP020A00F_OPMODE_ALS_AND_PS;
	} else {
		if (data->cur_opmode == GP2AP020A00F_OPMODE_ALS_AND_PS)
			new_mode = (diff_mode == GP2AP020A00F_OPMODE_ALS) ?
					GP2AP020A00F_OPMODE_PS :
					GP2AP020A00F_OPMODE_ALS;
		else
			new_mode = GP2AP020A00F_OPMODE_SHUTDOWN;
	}

	return gp2ap020a00f_set_operation_mode(data, new_mode);
}
