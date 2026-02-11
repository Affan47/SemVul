_cpp_save_parameter (pfile, macro, node)
     cpp_reader *pfile;
     cpp_macro *macro;
     cpp_hashnode *node;
{

  if (node->arg_index)
    {
      cpp_error (pfile, DL_ERROR, "duplicate macro parameter \"%s\"",
		 NODE_NAME (node));
      return true;
    }

  if (BUFF_ROOM (pfile->a_buff)
      < (macro->paramc + 1) * sizeof (cpp_hashnode *))
    _cpp_extend_buff (pfile, &pfile->a_buff, sizeof (cpp_hashnode *));

  ((cpp_hashnode **) BUFF_FRONT (pfile->a_buff))[macro->paramc++] = node;
  node->arg_index = macro->paramc;
  return false;
}
