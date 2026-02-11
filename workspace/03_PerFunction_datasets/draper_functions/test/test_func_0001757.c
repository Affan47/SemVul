walk_alter_subreg (rtx *xp, bool *changed)
{
  rtx x = *xp;
  switch (GET_CODE (x))
    {
    case PLUS:
    case MULT:
    case AND:
      XEXP (x, 0) = walk_alter_subreg (&XEXP (x, 0), changed);
      XEXP (x, 1) = walk_alter_subreg (&XEXP (x, 1), changed);
      break;

    case MEM:
    case ZERO_EXTEND:
      XEXP (x, 0) = walk_alter_subreg (&XEXP (x, 0), changed);
      break;

    case SUBREG:
      *changed = true;
      return alter_subreg (xp, true);

    default:
      break;
    }

  return *xp;
}
