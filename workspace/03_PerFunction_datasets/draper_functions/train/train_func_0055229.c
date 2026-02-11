adb_add_kbd_srq()
{
	if(g_kbd_reg3_16bit & 0x200) {

		g_adb_interrupt_byte |= 0x08;
		add_irq(IRQ_PENDING_ADB_KBD_SRQ);
	} else {
		printf("Got keycode but no kbd SRQ!\n");
	}
}
