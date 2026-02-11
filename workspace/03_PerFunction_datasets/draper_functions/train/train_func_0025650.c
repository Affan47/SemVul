o_move_return_whichone(OBJECT * object, int x, int y)
{
  if (object->line->x[0] == x && object->line->y[0] == y) {
    return (0);
  }

  if (object->line->x[1] == x && object->line->y[1] == y) {
    return (1);
  }

  fprintf(stderr,
          _("DOH! tried to find the whichone, but didn't find it!\n"));
  return (-1);
}
