xlockmore_read_resources (ModeInfo *mi)
{
  Display *dpy = mi->dpy;
  ModeSpecOpt *xlockmore_opts = mi->xlmft->opts;
  int i;
  for (i = 0; i < xlockmore_opts->numvarsdesc; i++)
    {
      void  *var   = xlockmore_opts->vars[i].var;
      Bool  *var_b = (Bool *)  var;
      char **var_c = (char **) var;
      int   *var_i = (int *) var;
      float *var_f = (float *) var;

      switch (xlockmore_opts->vars[i].type)
	{
	case t_String:
	  *var_c = get_string_resource (dpy, xlockmore_opts->vars[i].name,
					xlockmore_opts->vars[i].classname);
	  break;
	case t_Float:
	  *var_f = get_float_resource (dpy, xlockmore_opts->vars[i].name,
				       xlockmore_opts->vars[i].classname);
	  break;
	case t_Int:
	  *var_i = get_integer_resource (dpy, xlockmore_opts->vars[i].name,
					 xlockmore_opts->vars[i].classname);
	  break;
	case t_Bool:
	  *var_b = get_boolean_resource (dpy, xlockmore_opts->vars[i].name,
					 xlockmore_opts->vars[i].classname);
	  break;
	default:
	  abort ();
	}
    }
}
