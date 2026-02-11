new_line_sorts_after (struct line_info *new_line, struct line_info *line)
{
  return (new_line->address > line->address
	  || (new_line->address == line->address
	      && (new_line->op_index > line->op_index
		  || (new_line->op_index == line->op_index
		      && new_line->end_sequence < line->end_sequence))));
}
