epstool_bitmap(Doc *doc, OPT *opt)
{
    int code = 0;
    CDSCBBOX bbox;
    CDSCFBBOX hires_bbox;
    LPCTSTR device = COLOUR_DEVICE;
    int page = opt->page;
    if (opt->device[0] != '\0')
	device = opt->device;

    if (doc->dsc->bbox)
	bbox = *doc->dsc->bbox;
    else {
	bbox.llx = bbox.lly = bbox.urx = bbox.ury = 0;
	opt->bbox = 1;
    }

    if (doc->dsc->hires_bbox)
	hires_bbox = *doc->dsc->hires_bbox;
    else {
	hires_bbox.fllx = (float)bbox.llx;
	hires_bbox.flly = (float)bbox.lly;
	hires_bbox.furx = (float)bbox.urx;
	hires_bbox.fury = (float)bbox.ury;
    }

    if (doc->dsc->page_count == 0)
	page = 0;
    else if ((opt->page < 0) || (opt->page >= (int)doc->dsc->page_count))
	return -1;

    code = make_preview_file(doc, opt, page, opt->output,
	device, opt->dpi, &bbox, &hires_bbox, opt->bbox);

    return code;
}
