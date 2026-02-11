bt_ctf_clock_set_frequency(struct bt_ctf_clock *clock, uint64_t freq)
{
	int ret = 0;

	if (!clock || clock->frozen) {
		ret = -1;
		goto end;
	}

	clock->frequency = freq;
end:
	return ret;
}
