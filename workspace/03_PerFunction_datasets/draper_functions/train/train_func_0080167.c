print_mixer_chan(struct text_object *obj, int chan, char *p, int p_max_size)
{
	int val;

	if (chan < 0)
		val = mixer_get_left(obj->data.l);
	else if (chan == 0)
		val = mixer_get_avg(obj->data.l);
	else
		val = mixer_get_right(obj->data.l);

	percent_print(p, p_max_size, val);
}
