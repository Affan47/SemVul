oslec_free(struct oslec_state *ec)
{
	int i;

	fir16_free(&ec->fir_state);
	fir16_free(&ec->fir_state_bg);
	for (i = 0; i < 2; i++)
		kfree(ec->fir_taps16[i]);
	kfree(ec->snapshot);
	kfree(ec);
}
