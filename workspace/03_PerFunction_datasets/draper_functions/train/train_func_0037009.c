compute_e801(struct s_my_menu *menu)
{
    char buffer[MENULEN + 1];
    char statbuffer[STATLEN + 1];

    sprintf(buffer, " e801 information ");
    menu->items_count = 0;
    menu->menu = add_menu(buffer, -1);

    int mem_low, mem_high = 0;
    if (detect_memory_e801(&mem_low, &mem_high)) {
	snprintf(buffer, sizeof buffer, "%s", "e801 output is bogus");
	snprintf(statbuffer, sizeof statbuffer, "%s", "e801 output is bogus");
	add_item(buffer, statbuffer, OPT_INACTIVE, NULL, 0);
	menu->items_count++;
    } else {
	snprintf(buffer, sizeof buffer, "Detected Memory  : %d MiB (%d KiB)",
		 (mem_high >> 4) + (mem_low >> 10), mem_low + (mem_high << 6));
	snprintf(statbuffer, sizeof statbuffer,
		 "Detected Memory : %d MiB (%d KiB)",
		 (mem_high >> 4) + (mem_low >> 10), mem_low + (mem_high << 6));
	add_item(buffer, statbuffer, OPT_INACTIVE, NULL, 0);

	add_item("", "", OPT_SEP, "", 0);
	snprintf(buffer, sizeof buffer, "Low Memory       : %d KiB (%d MiB)",
		 mem_low, mem_low >> 10);
	snprintf(statbuffer, sizeof statbuffer, "Low Memory : %d KiB (%d MiB)",
		 mem_low, mem_low >> 10);
	add_item(buffer, statbuffer, OPT_INACTIVE, NULL, 0);

	snprintf(buffer, sizeof buffer, "High Memory      : %d KiB (%d MiB)",
		 mem_high << 6, mem_high >> 4);
	snprintf(statbuffer, sizeof statbuffer, "High Memory : %d KiB (%d MiB)",
		 mem_high << 6, mem_high >> 4);
	add_item(buffer, statbuffer, OPT_INACTIVE, NULL, 0);

    }
    menu->items_count++;
}
