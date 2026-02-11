free_screenlines()
{
#ifdef FEAT_MBYTE
    int		i;

    vim_free(ScreenLinesUC);
    for (i = 0; i < Screen_mco; ++i)
	vim_free(ScreenLinesC[i]);
    vim_free(ScreenLines2);
#endif
    vim_free(ScreenLines);
    vim_free(ScreenAttrs);
    vim_free(LineOffset);
    vim_free(LineWraps);
#ifdef FEAT_WINDOWS
    vim_free(TabPageIdxs);
#endif
}
