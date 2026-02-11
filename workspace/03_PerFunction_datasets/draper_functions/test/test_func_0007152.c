_update_line_numbers(gp_linenum_type *line_number, int offset)
{

  while (line_number != NULL) {
    line_number->address += offset;
    line_number = line_number->next;
  }

}
