put(unsigned int new_value)
{
  unsigned int old_value=value.get();
  new_value &= valid_bits;


  trace.raw(write_trace.get() | value.get());

  Dprintf(("ADCON0_12F::put new_value=0x%02x old_value=0x%02x\n", new_value, old_value));

  adcon1->set_cfg_index((new_value & VCFG) ? 2: 0);


  if ((new_value & ADON) != ADON)
	new_value &= ~GO_bit;


  value.put(new_value);
  if(new_value & ADON) {


    if((new_value & ~old_value) & GO_bit) {
      if (verbose)
	printf("starting A2D conversion\n");


      start_conversion();
    }
  } else
    stop_conversion();

}
