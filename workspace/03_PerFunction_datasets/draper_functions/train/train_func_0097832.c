atkbd_apply_forced_release_keylist(struct atkbd* atkbd,
						const void *data)
{
	const unsigned int *keys = data;
	unsigned int i;

	if (atkbd->set == 2)
		for (i = 0; keys[i] != -1U; i++)
			__set_bit(keys[i], atkbd->force_release_mask);
}
