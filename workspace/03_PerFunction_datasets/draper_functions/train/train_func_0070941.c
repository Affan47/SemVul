mch_print_cleanup()
{
#ifdef FEAT_MBYTE
    if (prt_out_mbyte)
    {
	int     i;


	for (i = PRT_PS_FONT_ROMAN; i <= PRT_PS_FONT_BOLDOBLIQUE; i++)
	{
	    if (prt_ps_mb_font.ps_fontname[i] != NULL)
		vim_free(prt_ps_mb_font.ps_fontname[i]);
	    prt_ps_mb_font.ps_fontname[i] = NULL;
	}
    }

    if (prt_do_conv)
    {
	convert_setup(&prt_conv, NULL, NULL);
	prt_do_conv = FALSE;
    }
#endif
    if (prt_ps_fd != NULL)
    {
	fclose(prt_ps_fd);
	prt_ps_fd = NULL;
	prt_file_error = FALSE;
    }
    if (prt_ps_file_name != NULL)
    {
	vim_free(prt_ps_file_name);
	prt_ps_file_name = NULL;
    }
}
