menu_offset(MenuNo number)
{
    int result = 0;

    if (okMenuNo(number)) {
	int spc_desc, spc_rows, spc_cols;

#ifdef NCURSES_VERSION
	menu_spacing(mpBanner, &spc_desc, &spc_rows, &spc_cols);
#else
	spc_rows = 0;
#endif


	result = (number - (eBanner + 1)) * (mpBanner->itemlen + spc_rows);
    }
    return result;
}
