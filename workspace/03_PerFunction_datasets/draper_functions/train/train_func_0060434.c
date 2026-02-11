button_kill_all(void)
{
	int i;


	if (!button_kill_hook) return;


	for (i = button_num - 1; i >= 0; i--)
		(void)(*button_kill_hook) (button_mse[i].key);
}
