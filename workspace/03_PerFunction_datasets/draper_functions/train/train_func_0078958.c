do_mem_probe(struct pcmcia_socket *s, u_long base, u_long num,
			int validate (struct pcmcia_socket *s,
				      struct resource *res,
				      unsigned int *value),
			int fallback (struct pcmcia_socket *s,
				      struct resource *res,
				      unsigned int *value))
{
	struct socket_data *s_data = s->resource_data;
	u_long i, j, bad, fail, step;

	dev_info(&s->dev, "cs: memory probe 0x%06lx-0x%06lx:",
		 base, base+num-1);
	bad = fail = 0;
	step = (num < 0x20000) ? 0x2000 : ((num>>4) & ~0x1fff);

	if (step > 0x800000)
		step = 0x800000;

	if (step < 2 * s->map_size)
		step = 2 * s->map_size;
	for (i = j = base; i < base+num; i = j + step) {
		if (!fail) {
			for (j = i; j < base+num; j += step) {
				if (!do_validate_mem(s, j, step, validate))
					break;
			}
			fail = ((i == base) && (j == base+num));
		}
		if ((fail) && (fallback)) {
			for (j = i; j < base+num; j += step)
				if (!do_validate_mem(s, j, step, fallback))
					break;
		}
		if (i != j) {
			if (!bad)
				pr_cont(" excluding");
			pr_cont(" %#05lx-%#05lx", i, j-1);
			sub_interval(&s_data->mem_db, i, j-i);
			bad += j-i;
		}
	}
	pr_cont("%s\n", !bad ? " clean" : "");
	return num - bad;
}
