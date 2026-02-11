handle_button(int event)
{
  int		i,
		X;
  char		*start,
		*end;
  char		newvalue[FL_PATH_MAX];


  for (X = 0, i = 0; buttons_[i]; i ++)
  {
    X += buttons_[i];

    if (X > xscroll() && Fl::event_x() < (x() + X - xscroll())) break;
  }


  if (event == FL_RELEASE) pressed_ = -1;
  else pressed_ = (short)i;

  window()->make_current();
  draw_buttons();


  if (!buttons_[i] || event != FL_RELEASE) return 1;


  strlcpy(newvalue, value(), sizeof(newvalue));

  for (start = newvalue, end = start; start && i >= 0; start = end, i --) {

    if ((end = strchr(start, '/')) == NULL)
#if defined(WIN32) || defined(__EMX__)
      if ((end = strchr(start, '\\')) == NULL)
#endif
      break;

    end ++;
  }

  if (i < 0) {

    *start = '\0';
    value(newvalue, (int) (start - newvalue) );


    set_changed();
    if (when() & (FL_WHEN_CHANGED|FL_WHEN_RELEASE) ) do_callback();
  }

  return 1;
}
