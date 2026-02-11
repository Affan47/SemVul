start_transmitting()
{
  Dprintf(("starting a USART transmission\n"));


  if(!txreg)
    return;

  tsr = txreg->value.get() << 1;


  if(value.get() & TX9)
    {


      tsr |= ( (value.get() & TX9D) ? (3<<9) : (2<<9));
      bit_count = 11;
    }
  else
    {


      tsr |= (1<<9);
      bit_count = 10;
    }


  if(cpu)
    get_cycles().set_break(spbrg->get_cpu_cycle(1), this);


  trace.raw(write_trace.get() | value.get());
  value.put(value.get() & ~TRMT);


  mUSART->emptyTX();

}
