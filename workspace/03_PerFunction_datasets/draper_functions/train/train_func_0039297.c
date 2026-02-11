sun4i_get_temp(const struct sun4i_ts_data *ts, int *temp)
{

	if (ts->temp_data == -1)
		return -EAGAIN;

	*temp = ts->temp_data * ts->temp_step - ts->temp_offset;

	return 0;
}
