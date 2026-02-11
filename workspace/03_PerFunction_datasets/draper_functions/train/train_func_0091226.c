push(unsigned int new_value)
{
  trace.raw(write_trace.get() | value.get());

  if(fifo_sp >= 2) {

    if (m_rcsta)
      m_rcsta->overrun();

    Dprintf(("receive overrun\n"));

  } else {

    Dprintf(("pushing uart reception onto rcreg stack, value received=0x%x\n",new_value));
    fifo_sp++;
    oldest_value = value.get();
    value.put(new_value);
  }

  mUSART->set_rcif();

}
