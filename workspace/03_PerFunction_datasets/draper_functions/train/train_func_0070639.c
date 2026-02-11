update_palette_bank(int newbank)
{
	if (gfx_palettebank != newbank)
	{
		force_partial_update(cpu_getscanline());
		gfx_palettebank = newbank;
	}
}
