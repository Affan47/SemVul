lineeditor_refresh
   ___P((___device_tty *self),
        (self)
___device_tty *self;)
{
  ___device_tty *d = self;
  ___SCMOBJ e;
  extensible_string *edited = &d->current.hist->edited;

  if ((e = lineeditor_output_set_attrs
             (d,
              lineeditor_erase_attrs (d)))
      == ___FIX(___NO_ERR))
    {
#ifdef USE_CURSES

      if (lineeditor_cap (d, LINEEDITOR_CAP_CLEAR) != NULL)
        e = lineeditor_output_cap0 (d, LINEEDITOR_CAP_CLEAR, 1);
      else

#endif

        e = lineeditor_left_margin_of_next_row (d);

      if (e == ___FIX(___NO_ERR))
        {
          lineeditor_output_prompt (d);

          d->current.line_start = d->terminal_cursor;

          if ((e = lineeditor_update_region (d, 0, edited->length))
              == ___FIX(___NO_ERR))
            e = lineeditor_move_edit_point (d, d->current.edit_point);
        }
    }

  return e;
}
