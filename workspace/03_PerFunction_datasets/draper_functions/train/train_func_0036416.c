add_partition_options(File fptr, partition_element *p_elem)
{
  int err= 0;

  err+= add_space(fptr);
  if (p_elem->tablespace_name)
    err+= add_keyword_string(fptr,"TABLESPACE", FALSE,
                             p_elem->tablespace_name);
  if (p_elem->nodegroup_id != UNDEF_NODEGROUP)
    err+= add_keyword_int(fptr,"NODEGROUP",(longlong)p_elem->nodegroup_id);
  if (p_elem->part_max_rows)
    err+= add_keyword_int(fptr,"MAX_ROWS",(longlong)p_elem->part_max_rows);
  if (p_elem->part_min_rows)
    err+= add_keyword_int(fptr,"MIN_ROWS",(longlong)p_elem->part_min_rows);
  if (!(current_thd->variables.sql_mode & MODE_NO_DIR_IN_CREATE))
  {
    if (p_elem->data_file_name)
      err+= add_keyword_string(fptr, "DATA DIRECTORY", TRUE,
                               p_elem->data_file_name);
    if (p_elem->index_file_name)
      err+= add_keyword_string(fptr, "INDEX DIRECTORY", TRUE,
                               p_elem->index_file_name);
  }
  if (p_elem->part_comment)
    err+= add_keyword_string(fptr, "COMMENT", TRUE, p_elem->part_comment);
  return err + add_engine(fptr,p_elem->engine_type);
}
