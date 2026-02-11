find_display (Display *display)
{


  pushSTACK(Symbol_value (O(object_xlib___2Adisplays_2A)));
  for (;consp (STACK_0); STACK_0 = Cdr (STACK_0)) {
    if (get_display(Car(STACK_0)) == display)
      return Car(popSTACK());
  }
  skipSTACK(1);
  return NIL;
}
