byt_freq_opcode(struct drm_i915_private *dev_priv, int val)
{
	int mul, czclk_freq = DIV_ROUND_CLOSEST(dev_priv->czclk_freq, 1000);

	mul = vlv_gpu_freq_div(czclk_freq);
	if (mul < 0)
		return mul;

	return DIV_ROUND_CLOSEST(mul * val, czclk_freq) + 0xbd - 6;
}
