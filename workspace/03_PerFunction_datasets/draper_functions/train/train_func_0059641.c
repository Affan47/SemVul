gf100_clk_prog(struct nvkm_clk *base)
{
	struct gf100_clk *clk = gf100_clk(base);
	struct {
		void (*exec)(struct gf100_clk *, int);
	} stage[] = {
		{ gf100_clk_prog_0 },
		{ gf100_clk_prog_1 },
		{ gf100_clk_prog_2 },
		{ gf100_clk_prog_3 },
		{ gf100_clk_prog_4 },
	};
	int i, j;

	for (i = 0; i < ARRAY_SIZE(stage); i++) {
		for (j = 0; j < ARRAY_SIZE(clk->eng); j++) {
			if (!clk->eng[j].freq)
				continue;
			stage[i].exec(clk, j);
		}
	}

	return 0;
}
