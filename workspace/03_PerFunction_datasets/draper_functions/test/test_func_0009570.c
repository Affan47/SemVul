doquit(struct io_data *io_data, __maybe_unused SOCKETTYPE c, __maybe_unused char *param, bool isjson, __maybe_unused char group)
{
	if (isjson)
		io_put(io_data, JSON_START JSON_BYE);
	else
		io_put(io_data, _BYE);

	bye = true;
	do_a_quit = true;
}
