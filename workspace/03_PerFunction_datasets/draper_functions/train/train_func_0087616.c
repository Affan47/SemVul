initialize_shell_options (no_shellopts)
     int no_shellopts;
{
  char *temp;
  SHELL_VAR *var;

  if (no_shellopts == 0)
    {
      var = find_variable ("SHELLOPTS");

      if (var && imported_p (var))
	{
	  temp = (array_p (var) || assoc_p (var)) ? (char *)NULL : savestring (value_cell (var));
	  if (temp)
	    {
	      parse_shellopts (temp);
	      free (temp);
	    }
	}
    }


  set_shellopts ();
}
