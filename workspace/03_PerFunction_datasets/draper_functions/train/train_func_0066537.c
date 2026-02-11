pop()
{

  if(fifo_sp == 0)
    return;

  if(--fifo_sp == 1)
    value.put(oldest_value);

  if(fifo_sp == 0)
    mUSART->clear_rcif();

}
