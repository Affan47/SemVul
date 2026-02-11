build_menus(char *filename)
{
    static CONST_MENUS char *labels[] =
    {
	"File",
	"Select",
#ifdef TRACE
	"Trace",
#endif
	(char *) 0
    };
    static ITEM *items[SIZEOF(labels)];

    ITEM **ip = items;
    CONST_MENUS char **ap;

    for (ap = labels; *ap; ap++)
	*ip++ = new_item(*ap, "");
    *ip = (ITEM *) 0;

    mpBanner = menu_create(items, SIZEOF(labels) - 1, SIZEOF(labels) - 1, eBanner);
    set_menu_mark(mpBanner, ">");

    build_file_menu(eFile);
    build_select_menu(eSelect, filename);
#ifdef TRACE
    build_trace_menu(eTrace);
#endif
}
