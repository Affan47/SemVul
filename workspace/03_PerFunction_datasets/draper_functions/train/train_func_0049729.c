type_to_char (a_dir dir)
{
  switch (dir) {
  case T_NONE:
    return ' ';
  case T_STOP:
    return 'h';
  case T_SPEED:
    return 's';
  case T_TUNNEL:
    return 't';
  case T_BOOM:
    return 'b';
  case T_ANIM:
    return 'a';
  case T_ICE:
    return 'i';
  case T_DUST:
    return 'd';
  case T_OUTWAY:
    return 'X';
  default:
    exit_status = 4;
    return '?';
  }
}
