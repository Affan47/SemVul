interrupt ()
{

  bp.clear_interrupt();

  if (bp.have_sleep()) {
      bp.clear_sleep();
      stack->push(pc->value+1);
  } else {
      stack->push(pc->value);
  }
  status_shad.value = status->value;
  wreg_shad.value = Wreg->value;
  bsr_shad.value = bsr.value;
  pclath_shad.value = pclath->value;
  fsr0l_shad.value = ind0.fsrl.value;
  fsr0h_shad.value = ind0.fsrh.value;
  fsr1l_shad.value = ind1.fsrl.value;
  fsr1h_shad.value = ind1.fsrh.value;
  intcon->clear_gie();

  pc->interrupt(INTERRUPT_VECTOR);

}
