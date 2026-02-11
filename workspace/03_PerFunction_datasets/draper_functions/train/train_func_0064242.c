c_plsdimap(PLINT dimxmin, PLINT dimxmax, PLINT dimymin, PLINT dimymax,
	   PLFLT dimxpmm, PLFLT dimypmm)
{
    plsetvar(plsc->dimxmin, dimxmin);
    plsetvar(plsc->dimxmax, dimxmax);
    plsetvar(plsc->dimymin, dimymin);
    plsetvar(plsc->dimymax, dimymax);
    plsetvar(plsc->dimxpmm, dimxpmm);
    plsetvar(plsc->dimypmm, dimypmm);

    plsc->difilt |= PLDI_MAP;
    pldi_ini();
}
