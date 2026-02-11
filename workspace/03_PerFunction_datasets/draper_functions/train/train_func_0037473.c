gui_init_font(font_list, fontset)
    char_u	*font_list;
    int		fontset UNUSED;
{
#define FONTLEN 320
    char_u	font_name[FONTLEN];
    int		font_list_empty = FALSE;
    int		ret = FAIL;

    if (!gui.in_use)
	return FAIL;

    font_name[0] = NUL;
    if (*font_list == NUL)
	font_list_empty = TRUE;
    else
    {
#ifdef FEAT_XFONTSET

	if (fontset)
	    ret = gui_mch_init_font(font_list, TRUE);
	else
#endif
	    while (*font_list != NUL)
	    {

		(void)copy_option_part(&font_list, font_name, FONTLEN, ",");


		if (gui_mch_init_font(font_name, FALSE) == OK)
		{
#if defined(FEAT_MBYTE) && !defined(FEAT_GUI_GTK)


		    if ((p_guifontwide == NULL || *p_guifontwide == NUL)
				&& strstr((char *)font_name, "10646") != NULL)
			set_guifontwide(font_name);
#endif
		    ret = OK;
		    break;
		}
	    }
    }

    if (ret != OK
	    && STRCMP(font_list, "*") != 0
	    && (font_list_empty || gui.norm_font == NOFONT))
    {


	ret = gui_mch_init_font(NULL, FALSE);
    }

    if (ret == OK)
    {
#ifndef FEAT_GUI_GTK

# ifdef FEAT_XFONTSET
	if (gui.fontset != NOFONTSET)
	    gui_mch_set_fontset(gui.fontset);
	else
# endif
	    gui_mch_set_font(gui.norm_font);
#endif
	gui_set_shellsize(FALSE, TRUE, RESIZE_BOTH);
    }

    return ret;
}
