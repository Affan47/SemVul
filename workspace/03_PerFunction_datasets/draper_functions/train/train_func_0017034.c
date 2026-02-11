check_for_stepping_quirk(struct samsung_laptop *samsung)
{
	int initial_level;
	int check_level;
	int orig_level = read_brightness(samsung);


	if (orig_level == 0)
		set_brightness(samsung, 1);

	initial_level = read_brightness(samsung);

	if (initial_level <= 2)
		check_level = initial_level + 2;
	else
		check_level = initial_level - 2;

	samsung->has_stepping_quirk = false;
	set_brightness(samsung, check_level);

	if (read_brightness(samsung) != check_level) {
		samsung->has_stepping_quirk = true;
		pr_info("enabled workaround for brightness stepping quirk\n");
	}

	set_brightness(samsung, orig_level);
}
