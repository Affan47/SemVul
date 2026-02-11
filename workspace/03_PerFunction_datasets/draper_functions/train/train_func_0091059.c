cond_finish_check (int nest)
{
  if (current_cframe != NULL && current_cframe->macro_nest >= nest)
    {
      if (nest >= 0)
	as_bad (_("end of macro inside conditional"));
      else
	as_bad (_("end of file inside conditional"));
      as_bad_where (current_cframe->if_file_line.file,
		    current_cframe->if_file_line.line,
		    _("here is the start of the unterminated conditional"));
      if (current_cframe->else_seen)
	as_bad_where (current_cframe->else_file_line.file,
		      current_cframe->else_file_line.line,
		      _("here is the \"else\" of the unterminated conditional"));
    }
}
