dce6_dmif_request_bandwidth(struct dce6_wm_params *wm)
{

	fixed20_12 disp_clk_request_efficiency;
	fixed20_12 disp_clk, sclk, bandwidth;
	fixed20_12 a, b1, b2;
	u32 min_bandwidth;

	a.full = dfixed_const(1000);
	disp_clk.full = dfixed_const(wm->disp_clk);
	disp_clk.full = dfixed_div(disp_clk, a);
	a.full = dfixed_const(dce6_get_dmif_bytes_per_request(wm) / 2);
	b1.full = dfixed_mul(a, disp_clk);

	a.full = dfixed_const(1000);
	sclk.full = dfixed_const(wm->sclk);
	sclk.full = dfixed_div(sclk, a);
	a.full = dfixed_const(dce6_get_dmif_bytes_per_request(wm));
	b2.full = dfixed_mul(a, sclk);

	a.full = dfixed_const(10);
	disp_clk_request_efficiency.full = dfixed_const(8);
	disp_clk_request_efficiency.full = dfixed_div(disp_clk_request_efficiency, a);

	min_bandwidth = min(dfixed_trunc(b1), dfixed_trunc(b2));

	a.full = dfixed_const(min_bandwidth);
	bandwidth.full = dfixed_mul(a, disp_clk_request_efficiency);

	return dfixed_trunc(bandwidth);
}
