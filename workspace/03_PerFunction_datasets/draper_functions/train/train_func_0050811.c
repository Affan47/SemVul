pico_sendexit_for_adrbk(struct headerentry *he, void (*redraw_pico)(void),
			int allow_flowed, char **result)
{
    char *rstr = NULL;
    void (*redraw)(void) = ps_global->redrawer;

    ps_global->redrawer = redraw_pico;
    fix_windsize(ps_global);


    switch(want_to(_("Exit and save changes "), 'y', 0, NO_HELP, WT_NORM)){
      case 'y':
	break;

      case 'n':
	rstr = _("Use ^C to abandon changes you've made");
	break;
    }

    if(result)
      *result = rstr;

    ps_global->redrawer = redraw;
    return((rstr == NULL) ? 0 : 1);
}
