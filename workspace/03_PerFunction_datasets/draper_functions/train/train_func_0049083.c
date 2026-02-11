Stream_Get_Position(StmInf *pstm, int *offset, int *char_count,
		    int *line_count, int *line_pos)
{
  long file = pstm->file;

  *offset = 0;
  if (pstm->prop.reposition && pstm->fct_tell != STREAM_FCT_UNDEFINED)
    {
      if ((*offset = (*pstm->fct_tell) (file)) < 0)
	*offset = 0;
      else
	{
	  *offset = *offset - pstm->pb_char.nb_elems;
	  if (*offset < 0)
	    *offset = 0;
	}
    }

  *char_count = pstm->char_count;

  if (pstm->prop.text)
    {
      *line_count = pstm->line_count;
      *line_pos = pstm->line_pos;
    }
  else
    {
      *line_count = 0;
      *line_pos = 0;
    }
}
