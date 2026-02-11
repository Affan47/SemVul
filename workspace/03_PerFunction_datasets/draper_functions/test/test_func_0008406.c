add_header_color_line(struct pine *ps, CONF_S **ctmp, char *val, int which)
{
    struct variable *vtmp;
    SPEC_COLOR_S     *hc;
    char	     tmp[100+1];
    int              l;

    vtmp = &ps->vars[V_VIEW_HDR_COLORS];
    l = strlen(HEADER_WORD);


    new_confline(ctmp);
    (*ctmp)->flags		|= CF_NOSELECT | CF_B_LINE;

    new_confline(ctmp)->var	 = vtmp;
    (*ctmp)->varnamep		 = *ctmp;
    (*ctmp)->keymenu		 = &custom_color_setting_keymenu;
    (*ctmp)->help		 = config_help(vtmp - ps->vars, 0);
    (*ctmp)->tool		 = color_setting_tool;
    (*ctmp)->flags |= (CF_STARTITEM | CF_COLORSAMPLE | CF_POT_SLCTBL);
    if(!pico_usingcolor())
      (*ctmp)->flags |= CF_NOSELECT;


    (*ctmp)->varmem		 = CFC_SET_COLOR(which, 0);

    hc = spec_color_from_var(val, 0);
    if(hc && hc->inherit)
      (*ctmp)->flags = (CF_NOSELECT | CF_INHERIT);
    else{


	utf8_snprintf(tmp, sizeof(tmp), "%s%c%.*w Color%*w %s%s",
		HEADER_WORD,
		(hc && hc->spec) ? (islower((unsigned char)hc->spec[0])
					    ? toupper((unsigned char)hc->spec[0])
					    : hc->spec[0]) : '?',
		MIN(utf8_width((hc && hc->spec && hc->spec[0]) ? hc->spec+1 : ""),30-l),
		(hc && hc->spec && hc->spec[0]) ? hc->spec+1 : "",
		MAX(EQ_COL - COLOR_INDENT -1 -
		   MIN(utf8_width((hc && hc->spec && hc->spec[0]) ? hc->spec+1 : ""),30-l)
			    - l - 6 - 1, 0), "",
		sample_text(ps,vtmp),
		color_parenthetical(vtmp));
	tmp[sizeof(tmp)-1] = '\0';
	(*ctmp)->value		 = cpystr(tmp);
    }

    (*ctmp)->valoffset		 = COLOR_INDENT;

    if(hc)
      free_spec_colors(&hc);
}
