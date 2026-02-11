add_mark(void)
{
	int letter;

	print_statusline("Mark: ");
	letter = less_getch(sizeof("Mark: ") - 1);

	if (isalpha(letter)) {

		if (num_marks == 14)
			num_marks = 0;

		mark_lines[num_marks][0] = letter;
		mark_lines[num_marks][1] = cur_fline;
		num_marks++;
	} else {
		print_statusline("Invalid mark letter");
	}
}
