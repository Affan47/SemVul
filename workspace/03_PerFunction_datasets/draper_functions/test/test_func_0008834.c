handle(int event) {
  double v;
  int delta;
  int mx = Fl::event_x_root();
  static int ix, drag;
  input.when(when());
  switch (event) {
  case FL_PUSH:
    if (!step()) goto DEFAULT;
    ix = mx;
    drag = Fl::event_button();
    handle_push();
    return 1;
  case FL_DRAG:
    if (!step()) goto DEFAULT;
    delta = mx-ix;
    if (delta > 5) delta -= 5;
    else if (delta < -5) delta += 5;
    else delta = 0;
    switch (drag) {
    case 3: v = increment(previous_value(), delta*100); break;
    case 2: v = increment(previous_value(), delta*10); break;
    default:v = increment(previous_value(), delta); break;
    }
    v = round(v);
    handle_drag(soft()?softclamp(v):clamp(v));;
    return 1;
  case FL_RELEASE:
    if (!step()) goto DEFAULT;
    if (value() != previous_value() || !Fl::event_is_click())
      handle_release();
    else {
      Fl_Widget_Tracker wp(&input);
      input.handle(FL_PUSH);
      if (wp.exists())
	input.handle(FL_RELEASE);
    }
    return 1;
  case FL_FOCUS:
    return input.take_focus();
  case FL_SHORTCUT:
    return input.handle(event);
  default:
  DEFAULT:
    input.type(((step() - floor(step()))>0.0 || step() == 0.0) ? FL_FLOAT_INPUT : FL_INT_INPUT);
    return input.handle(event);
  }
}
