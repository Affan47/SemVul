convert_free(struct convert_rock *rock) {
    struct convert_rock *next;
    while (rock) {
	next = rock->next;
	if (rock->cleanup)
	    rock->cleanup(rock);
	else
	    basic_free(rock);
	rock = next;
    }
}
