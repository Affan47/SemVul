inherit_font_change(GRE *gre, int childindex, int cid_off,
	void *whatever) {
    GGadget *g = GWidgetGetControl(gre->gw,gre->tofree[childindex].fontcid);
    struct inherit_font_data *ifd = (struct inherit_font_data *) whatever;

    if ( ifd->font!=NULL )
	*(gre->tofree[childindex].res->font) = ifd->font;
    GGadgetSetTitle8(g,ifd->spec);
}
