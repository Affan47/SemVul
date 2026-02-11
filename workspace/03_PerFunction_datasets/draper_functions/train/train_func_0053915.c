panel_scan_timer(void)
{
	if (keypad.enabled && keypad_initialized) {
		if (spin_trylock_irq(&pprt_lock)) {
			phys_scan_contacts();


			spin_unlock_irq(&pprt_lock);
		}

		if (!inputs_stable || phys_curr != phys_prev)
			panel_process_inputs();
	}

	if (lcd.enabled && lcd.initialized) {
		if (keypressed) {
			if (lcd.light_tempo == 0 &&
			    ((lcd.flags & LCD_FLAG_L) == 0))
				lcd_backlight(1);
			lcd.light_tempo = FLASH_LIGHT_TEMPO;
		} else if (lcd.light_tempo > 0) {
			lcd.light_tempo--;
			if (lcd.light_tempo == 0 &&
			    ((lcd.flags & LCD_FLAG_L) == 0))
				lcd_backlight(0);
		}
	}

	mod_timer(&scan_timer, jiffies + INPUT_POLL_TIME);
}
