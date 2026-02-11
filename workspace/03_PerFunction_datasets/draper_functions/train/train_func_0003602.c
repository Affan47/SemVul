_cpp_handle_directive (pfile, indented)
     cpp_reader *pfile;
     int indented;
{
  const directive *dir = 0;
  const cpp_token *dname;
  bool was_parsing_args = pfile->state.parsing_args;
  int skip = 1;

  if (was_parsing_args)
    {
      if (CPP_OPTION (pfile, pedantic))
	cpp_error (pfile, DL_PEDWARN,
	     "embedding a directive within macro arguments is not portable");
      pfile->state.parsing_args = 0;
      pfile->state.prevent_expansion = 0;
    }
  start_directive (pfile);
  dname = _cpp_lex_token (pfile);

  if (dname->type == CPP_NAME)
    {
      if (dname->val.node->directive_index)
	dir = &dtable[dname->val.node->directive_index - 1];
    }


  else if (dname->type == CPP_NUMBER && CPP_OPTION (pfile, lang) != CLK_ASM)
    {
      dir = &linemarker_dir;
      if (CPP_PEDANTIC (pfile) && ! CPP_OPTION (pfile, preprocessed)
	  && ! pfile->state.skipping)
	cpp_error (pfile, DL_PEDWARN,
		   "style of line directive is a GCC extension");
    }

  if (dir)
    {


      if (! (dir->flags & IF_COND))
	pfile->mi_valid = false;


      if (CPP_OPTION (pfile, preprocessed)
	  && (indented || !(dir->flags & IN_I)))
	{
	  skip = 0;
	  dir = 0;
	}
      else
	{


	  pfile->state.angled_headers = dir->flags & INCL;
	  pfile->state.directive_wants_padding = dir->flags & INCL;
	  if (! CPP_OPTION (pfile, preprocessed))
	    directive_diagnostics (pfile, dir, indented);
	  if (pfile->state.skipping && !(dir->flags & COND))
	    dir = 0;
	}
    }
  else if (dname->type == CPP_EOF)
    ;
  else
    {


      if (CPP_OPTION (pfile, lang) == CLK_ASM)
	skip = 0;
      else if (!pfile->state.skipping)
	cpp_error (pfile, DL_ERROR, "invalid preprocessing directive #%s",
		   cpp_token_as_text (pfile, dname));
    }

  pfile->directive = dir;
  if (CPP_OPTION (pfile, traditional))
    prepare_directive_trad (pfile);

  if (dir)
    (*pfile->directive->handler) (pfile);
  else if (skip == 0)
    _cpp_backup_tokens (pfile, 1);

  end_directive (pfile, skip);
  if (was_parsing_args)
    {

      pfile->state.parsing_args = 2;
      pfile->state.prevent_expansion = 1;
      pfile->buffer->saved_flags |= PREV_WHITE;
    }
  return skip;
}
