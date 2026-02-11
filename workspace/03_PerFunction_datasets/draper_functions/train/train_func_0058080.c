ath6kl_cookie_init(struct ath6kl *ar)
{
	u32 i;

	ar->cookie_list = NULL;
	ar->cookie_count = 0;

	memset(ar->cookie_mem, 0, sizeof(ar->cookie_mem));

	for (i = 0; i < MAX_COOKIE_NUM; i++)
		ath6kl_free_cookie(ar, &ar->cookie_mem[i]);
}
