check_console(struct work_struct *work)
{
	s32 bytes_read, tries, total_read;
	struct octeon_console *console;
	struct cavium_wk *wk = (struct cavium_wk *)work;
	struct octeon_device *oct = (struct octeon_device *)wk->ctxptr;
	size_t console_num = wk->ctxul;
	u32 delay;

	console = &oct->console[console_num];
	tries = 0;
	total_read = 0;

	do {


		bytes_read =
			octeon_console_read(oct, console_num, console_buffer,
					    sizeof(console_buffer) - 1, 0);
		if (bytes_read > 0) {
			total_read += bytes_read;
			if (console->waiting) {
				octeon_console_handle_result(oct, console_num,
							     console_buffer,
							     bytes_read);
			}
			if (octeon_console_debug_enabled(console_num)) {
				output_console_line(oct, console, console_num,
						    console_buffer, bytes_read);
			}
		} else if (bytes_read < 0) {
			dev_err(&oct->pci_dev->dev, "Error reading console %lu, ret=%d\n",
				console_num, bytes_read);
		}

		tries++;
	} while ((bytes_read > 0) && (tries < 16));


	if (octeon_console_debug_enabled(console_num) &&
	    (total_read == 0) && (console->leftover[0])) {
		dev_info(&oct->pci_dev->dev, "%lu: %s\n",
			 console_num, console->leftover);
		console->leftover[0] = '\0';
	}

	delay = OCTEON_CONSOLE_POLL_INTERVAL_MS;

	schedule_delayed_work(&wk->work, msecs_to_jiffies(delay));
}
