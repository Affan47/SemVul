soft_reset(void)
{
	int i;
	struct cs5535_mfgpt_timer t;

	for (i = 0; i < MFGPT_MAX_TIMERS; i++) {
		t.nr = i;

		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP1, MFGPT_EVENT_RESET, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP2, MFGPT_EVENT_RESET, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP1, MFGPT_EVENT_NMI, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP2, MFGPT_EVENT_NMI, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP1, MFGPT_EVENT_IRQ, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP2, MFGPT_EVENT_IRQ, 0);
	}
}
