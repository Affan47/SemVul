Adjust_Cursor_Position(FORM *form, const FIELD_CELL *pos)
{
  FIELD *field;
  int idx;

  field = form->current;
  assert(pos >= field->buf && field->dcols > 0);
  idx = (int)(pos - field->buf);
#if USE_DIV_T
  *((div_t *) & (form->currow)) = div(idx, field->dcols);
#else
  form->currow = idx / field->dcols;
  form->curcol = idx - field->cols * form->currow;
#endif
  if (field->drows < form->currow)
    form->currow = 0;
}
