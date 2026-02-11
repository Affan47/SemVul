sleep()
{
    m_sleeping = true;
    Dprintf(("TMRL::sleep t1sysc %d\n", t1con->get_t1sync()));

    if (  t1con->get_tmr1on() && t1con->get_tmr1cs() < 2)
    {
      if (future_cycle)
      {
        current_value();
        get_cycles().clear_break(this);
	future_cycle = 0;
      }
    }
}
