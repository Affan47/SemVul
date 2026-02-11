TTL74153_config(int which, const struct TTL74153_interface *intf)
{
	if (which >= MAX_TTL74153)
	{
		logerror("Only %d 74153's are supported at this time.\n", MAX_TTL74153);
		return;
	}


	chips[which].output_cb = (intf ? intf->output_cb : 0);
	chips[which].a = 1;
	chips[which].b = 1;
	chips[which].enable[0] = 1;
	chips[which].enable[1] = 1;
	chips[which].input_lines[0][0] = 1;
	chips[which].input_lines[0][1] = 1;
	chips[which].input_lines[0][2] = 1;
	chips[which].input_lines[0][3] = 1;
	chips[which].input_lines[1][0] = 1;
	chips[which].input_lines[1][1] = 1;
	chips[which].input_lines[1][2] = 1;
	chips[which].input_lines[1][3] = 1;

	chips[which].last_output[0] = -1;
	chips[which].last_output[1] = -1;
}
