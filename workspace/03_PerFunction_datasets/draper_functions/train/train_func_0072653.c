kbd_init_tokens(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(kbd_tokens); ++i)
		if (find_token_id(kbd_tokens[i]) != -1)
			kbd_token_bits |= BIT(i);
}
