infix_set_break(offset location)
{
  breakpoint newbreak;

  infix_location cur_location;

  if(location == 0) {
    infix_print_string("No code at that location.\n");
    return 0;
  }

  newbreak.number = breaknumber++;
  newbreak.enabled = TRUE;
  newbreak.type = bp_break;
  newbreak.disposition = donttouch;
  newbreak.PC = location;
  newbreak.break_frame = -1;
  newbreak.hit_count = 0;
  newbreak.ignore_count = 0;
  newbreak.condition = NULL;

  LEadd(breaklist, newbreak);

  infix_print_string("Breakpoint ");
  infix_print_number(newbreak.number);
  infix_print_string(" at ");
  infix_print_number(location);

  if(infix_decode_PC(&cur_location, location)) {
    infix_print_string(": file ");
    infix_print_string(cur_location.file->filename);
    infix_print_string(", line ");
    infix_print_number(cur_location.line_num);
  }
  infix_print_string(".\n");

  do_check_watches = TRUE;
  return newbreak.number;
}
