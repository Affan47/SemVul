rj54n1_set_clock(struct i2c_client *client)
{
	struct rj54n1 *rj54n1 = to_rj54n1(client);
	int ret;


	ret = reg_write(client, RJ54N1_RESET_STANDBY, E_EXCLK | SOFT_STDBY);

	if (!ret)
		ret = reg_write(client, RJ54N1_RESET_STANDBY, E_EXCLK);

	if (!ret)
		ret = reg_write(client, RJ54N1_PLL_L, PLL_L);
	if (!ret)
		ret = reg_write(client, RJ54N1_PLL_N, PLL_N);


	if (!ret)
		ret = reg_write(client, RJ54N1_RATIO_TG,
				rj54n1->clk_div.ratio_tg);
	if (!ret)
		ret = reg_write(client, RJ54N1_RATIO_T,
				rj54n1->clk_div.ratio_t);
	if (!ret)
		ret = reg_write(client, RJ54N1_RATIO_R,
				rj54n1->clk_div.ratio_r);


	if (!ret)
		ret = reg_write(client, RJ54N1_RAMP_TGCLK_EN, 3);


	if (!ret)
		ret = reg_write(client, RJ54N1_OCLK_DSP, 0);


	if (!ret)
		ret = reg_write(client, RJ54N1_RATIO_OP,
				rj54n1->clk_div.ratio_op);
	if (!ret)
		ret = reg_write(client, RJ54N1_RATIO_O,
				rj54n1->clk_div.ratio_o);


	if (!ret)
		ret = reg_write(client, RJ54N1_OCLK_SEL_EN, 1);


	if (!ret)
		ret = reg_write(client, RJ54N1_TG_BYPASS, 2);


	if (!ret)
		ret = reg_write(client, RJ54N1_RESET_STANDBY,
				E_EXCLK | SEN_RSTX);

	if (!ret)
		ret = reg_write(client, RJ54N1_PLL_EN, 1);


	msleep(10);


	if (!ret)
		ret = reg_write(client, RJ54N1_CLK_RST, 1);

	if (!ret)
		ret = reg_read(client, RJ54N1_CLK_RST);
	if (ret != 1) {
		dev_err(&client->dev,
			"Resetting RJ54N1CB0C clock failed: %d!\n", ret);
		return -EIO;
	}


	ret = reg_set(client, RJ54N1_OCLK_DSP, 1, 1);


	if (!ret)
		ret = reg_write(client, RJ54N1_OCLK_SEL_EN, 1);

	return ret;
}
