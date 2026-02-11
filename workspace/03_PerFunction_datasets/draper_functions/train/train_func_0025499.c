PBI_BB_Menu(void)
{
	if (!PBI_BB_enabled) return;
	if (buttondown == FALSE) {
		D(printf("blackbox button down interrupt generated\n"));
		CPU_GenerateIRQ();
		PBI_IRQ |= BB_BUTTON_IRQ_MASK;
		buttondown = TRUE;
	}
}
