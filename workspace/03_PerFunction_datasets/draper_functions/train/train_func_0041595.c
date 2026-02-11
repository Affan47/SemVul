do_colormap(int& ct) {
	g_colormap = new GLEColorMap();
	g_colormap->setFunction(tk[++ct]);
	g_colormap->setWidth((int)floor(next_exp+0.5));
	g_colormap->setHeight((int)floor(next_exp+0.5));
	ct++;
	while (ct <= ntk) {
		kw("COLOR") g_colormap->setColor(true);
		kw("INVERT") g_colormap->setInvert(true);
		kw("ZMIN") g_colormap->setZMin(next_exp);
		kw("ZMAX") g_colormap->setZMax(next_exp);
		kw("PALETTE") {
			string tmp;
			next_str_cpp(tmp);
			str_to_uppercase(tmp);
			g_colormap->setPalette(tmp);
		}
		ct++;
	}
	g_colormap->readData();
}
