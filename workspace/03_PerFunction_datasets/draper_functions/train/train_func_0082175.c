get_best_pll_config(int clk)
{
	struct via_pll_config config;

	switch (viaparinfo->chip_info->gfx_chip_name) {
	case UNICHROME_CLE266:
	case UNICHROME_K400:
		config = get_pll_config(cle266_pll_limits,
			ARRAY_SIZE(cle266_pll_limits), clk);
		break;
	case UNICHROME_K800:
	case UNICHROME_PM800:
	case UNICHROME_CN700:
		config = get_pll_config(k800_pll_limits,
			ARRAY_SIZE(k800_pll_limits), clk);
		break;
	case UNICHROME_CX700:
	case UNICHROME_CN750:
	case UNICHROME_K8M890:
	case UNICHROME_P4M890:
	case UNICHROME_P4M900:
	case UNICHROME_VX800:
		config = get_pll_config(cx700_pll_limits,
			ARRAY_SIZE(cx700_pll_limits), clk);
		break;
	case UNICHROME_VX855:
	case UNICHROME_VX900:
		config = get_pll_config(vx855_pll_limits,
			ARRAY_SIZE(vx855_pll_limits), clk);
		break;
	}

	return config;
}
