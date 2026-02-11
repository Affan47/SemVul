set_callback_break(unsigned int spbrg_edge)
{
  unsigned int time_to_event;

  if(cpu && spbrg)
  {
    time_to_event = ( spbrg->get_cycles_per_tick() * spbrg_edge ) / TOTAL_SAMPLE_STATES;
    get_cycles().set_break(get_cycles().get() + time_to_event, this);
  }
}
