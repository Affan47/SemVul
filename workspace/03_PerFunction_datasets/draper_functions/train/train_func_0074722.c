SR_Start_Module_3(WamWord module_name_word, WamWord interface_word,
		  WamWord err_word)
{
  SRInf *sr = cur_sr;
  int atom_module_name = Rd_Atom_Check(module_name_word);
  Bool interface = Rd_Boolean(interface_word);
  SRModule *m;

  *glob_buff = '\0';

  for(m = sr->module_lst; m; m = m->next)
    if (m->atom_module_name == atom_module_name)
      break;

  if (m == NULL)
    {
      if (!interface)
	{
	  sprintf(glob_buff, "module(%s) not encoutered - interface assumed empty",
		  atom_tbl[atom_module_name].name);
	}
      m = (SRModule *) Malloc(sizeof(SRModule));
      m->atom_module_name = atom_module_name;
      m->i_atom_file_def = sr->file_top->atom_file_name;
      m->i_line_def = sr->cur_l1;
      m->b_atom_file_def = -1;
      m->b_line_def = 0;
      m->direct_lst.first = NULL;
      m->direct_lst.last = NULL;
      m->next = sr->module_lst;
      sr->module_lst = m;
    }
  else
    {
      if (interface)
	{
	  sprintf(glob_buff, "module(%s) already found at %s:%d - directive ignored",
		  atom_tbl[atom_module_name].name,
		  atom_tbl[m->i_atom_file_def].name,
		  m->i_line_def);
	  goto error;
	}
    }

  if (sr->cur_module)
    {
      sprintf(glob_buff, "end_%s(%s) not encoutered - assumed found",
	      Interf_Body(sr->interface),
	      atom_tbl[sr->cur_module->atom_module_name].name);

      Close_Current_Module();
    }

  if (!interface)
    {
      m->b_atom_file_def = sr->file_top->atom_file_name;
      m->b_line_def = sr->cur_l1;
    }

  sr->cur_module = m;
  sr->interface = interface;

  Do_Directives(&m->direct_lst);

  if (*glob_buff)
    {
    error:
      Un_String(glob_buff, err_word);
    }
}
