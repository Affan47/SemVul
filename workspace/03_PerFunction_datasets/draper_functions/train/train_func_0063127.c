display_menu(void)
{
    int left, right;
    int i;

    left = first;
    right = first + 15;

    for (i = 0; i < 15; i++) {
	if (left >= last)
	    break;
	if (right >= last)
	    fprintf(stdout, "  %-35.35s\n", text[left]);
	else
	    fprintf(stdout, "  %-35.35s  %-35.35s\n", text[left],
		    text[right]);

	left++;
	right++;
    }

    return 0;
}
