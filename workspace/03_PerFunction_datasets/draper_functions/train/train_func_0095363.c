execute(CMD_Args *args, CMD_Context context)
    {
      switch (context)
	{
	case 0:
	  if (args == NULL)
	    return;
	  if (_w->is_visible())
	    _w->update(args->get_long_arg("gap"));
	  break;
	case 1:
	  if (args == NULL)
	    return;
	  _w->selected(args->get_string_arg("filename"));
	  break;
	case 2:
	  _w->selected(NULL);
	  break;
	}
    }
}
