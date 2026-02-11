set_debug(const char *val, struct kernel_param *kp)
{
	int ret;
	struct sfax_hw *card;

	ret = param_set_uint(val, kp);
	if (!ret) {
		read_lock(&card_lock);
		list_for_each_entry(card, &Cards, list)
			_set_debug(card);
		read_unlock(&card_lock);
	}
	return ret;
}
