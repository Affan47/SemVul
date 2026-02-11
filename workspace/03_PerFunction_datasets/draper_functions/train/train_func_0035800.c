read_xx_legs (FILE *fxl, struct LEG **L) {
	GMT_LONG nlegs = 0;
	struct LEG *new_leg, *last_leg, *leg_head;
	leg_head = make_leg("-----");
	new_leg = make_leg("-----");
	last_leg = leg_head;
	while (fread((void *)new_leg, sizeof(struct LEG), (size_t)1, fxl) == 1) {
		nlegs++;
		last_leg->next_leg = new_leg;
		last_leg = last_leg->next_leg;
		new_leg = make_leg("-----");
	}
	free((char *) new_leg);
	*L = leg_head;
	return (nlegs);
}
