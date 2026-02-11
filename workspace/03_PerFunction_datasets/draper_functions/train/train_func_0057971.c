on_or_off(int new_state)
{

  if(new_state) {

    Dprintf(("TMR1 is being turned on\n"));


    last_cycle = (gint64)(get_cycles().get() -
	(value.get() + (tmrh->value.get()<<8)) * prescale * ext_scale + 0.5);
    update();
  }
  else {

    Dprintf(("TMR1 is being turned off\n"));


    current_value();
    if (future_cycle)
    {
        get_cycles().clear_break(this);
	future_cycle = 0;
    }
  }

}
