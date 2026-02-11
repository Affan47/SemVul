pet_unlocktarget(struct pet_data *pd)
{
	nullpo_retr(0, pd);

	pd->target_id = 0;

	return 0;
}
