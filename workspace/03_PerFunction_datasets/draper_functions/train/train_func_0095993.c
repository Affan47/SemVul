mix_colors(fireshell *fs)
{
	float flash;
	fs->h = rnd(360);
	fs->s = frand(0.4) + 0.6;
	fs->v = 1.0;
	fs_roll_rgb(fs);

	flash = rnd(444) + 111;
	fs->flash_r = fs->r * flash;
	fs->flash_g = fs->g * flash;
	fs->flash_b = fs->b * flash;
}
