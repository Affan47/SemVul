getSurface(void)
{
	int videlBpp = getBpp();
	int bpp = (videlBpp<=8) ? 8 : 16;
	int width = getWidth();
	int height = getHeight();

	if (width<64) {
		width = 64;
	}
	if (height<64) {
		height = 64;
	}

	if (surface) {
		if (prevVidelBpp == bpp) {
			if ((prevVidelWidth!=width) || (prevVidelHeight!=height)) {
				surface->resize(width, height);
				delete crcList;
				crcList = NULL;
			}
		} else {
			delete surface;
			surface = NULL;
			delete crcList;
			crcList = NULL;
		}
	}
	if (surface==NULL) {
		surface = host->video->createSurface(width,height,bpp);
	}
	if (crcList==NULL) {
		int crcWidth = surface->getDirtyWidth();
		int crcHeight = surface->getDirtyHeight();
		crcList = new Uint32[crcWidth*crcHeight];
		memset(crcList, 0, sizeof(Uint32)*crcWidth*crcHeight);
	}


	if ((prevVidelBpp == 16) && (bpp != 16))
		updatePalette = true;

	prevVidelWidth = width;
	prevVidelHeight = height;
	prevVidelBpp = bpp;

	refreshScreen();

	if (bx_options.opengl.enabled && bx_options.autozoom.enabled) {
		surface->setParam(HostSurface::SURF_DRAW, HostSurface::DRAW_RESCALE);
	}

	return surface;
}
