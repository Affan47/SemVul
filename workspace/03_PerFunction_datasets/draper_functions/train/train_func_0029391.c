crypt_iv_lmk_wipe(struct crypt_config *cc)
{
	struct iv_lmk_private *lmk = &cc->iv_gen_private.lmk;

	if (lmk->seed)
		memset(lmk->seed, 0, LMK_SEED_SIZE);

	return 0;
}
