html_href(htmloutput *ho, htmlfile *thisfile,
		      htmlfile *targetfile, char *targetfrag)
{
    rdstringc rs = { 0, 0, NULL };
    char *url;

    if (targetfile != thisfile)
	rdaddsc(&rs, targetfile->filename);
    if (targetfrag) {
	rdaddc(&rs, '#');
	rdaddsc(&rs, targetfrag);
    }
    url = rs.text;

    element_open(ho, "a");
    element_attr(ho, "href", url);
    sfree(url);
}
