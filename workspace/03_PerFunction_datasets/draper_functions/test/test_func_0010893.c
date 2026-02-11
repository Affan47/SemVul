execute(CMD_Args *args, CMD_Context context)
    {
      const char *name;

      switch (context)
        {
	case 0:
	  if (args == NULL)
	    args = new CMD_Args();

	  name = _w->tapeGetName(_w->tapeGetSelected());
	  args->set_string_arg("filename", name);
	  args->set_string_arg("tape-filename", name);
	  args->set_string_arg("tape-rename-title",
			       _("Please enter the new name for the file."));
	  args->add_callback("ui-tape-name-edit-CB-ok", this, 1);
	  CMD_EXEC_ARGS("ui-tape-name-edit", args);
	  break;
	case 1:
	  if (args == NULL)
	    return;


	  CMD_EXEC_ARGS("tape-rename-file", args);
	  break;
	}
    }
