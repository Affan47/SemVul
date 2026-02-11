install_fake_fb(int w, int h, int bpp) {
	int bpc;
	if (! screen) {
		return;
	}
	lock_client_sends(1);
	if (fake_fb) {
		free(fake_fb);
	}
	fake_fb = (char *) calloc(w*h*bpp/8, 1);
	if (! fake_fb) {
		rfbLog("could not create fake fb: %dx%d %d\n", w, h, bpp);
		lock_client_sends(0);
		return;
	}
	bpc = guess_bits_per_color(bpp);
	rfbLog("installing fake fb: %dx%d %d\n", w, h, bpp);
	rfbLog("rfbNewFramebuffer(0x%x, 0x%x, %d, %d, %d, %d, %d)\n",
	    screen, fake_fb, w, h, bpc, 1, bpp/8);

	rfb_new_framebuffer(screen, fake_fb, w, h, bpc, 1, bpp/8);
	lock_client_sends(0);
}
