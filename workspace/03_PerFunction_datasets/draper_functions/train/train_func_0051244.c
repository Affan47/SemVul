value_in_set_display_error(
        const void *value, const CheckIntegerSet * const check_integer_set,
        const int invert) {
	int succeeded = invert;
	assert_true(check_integer_set);
	{
		const void ** const set = check_integer_set->set;
		const size_t size_of_set = check_integer_set->size_of_set;
		size_t i;
		for (i = 0; i < size_of_set; i++) {
			if (set[i] == value) {
				if (invert) {
					succeeded = 0;
				}
				break;
			}
		}
		if (succeeded) {
			return 1;
		}
		print_error("%d is %sin the set (", value, invert ? "" : "not ");
		for (i = 0; i < size_of_set; i++) {
			print_error("%d, ", set[i]);
		}
		print_error(")\n");
	}
	return 0;
}
