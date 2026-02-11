execute(void)
{
  cpu14->pc->new_address(cpu14->stack->pop());
  cpu14->intcon->set_gie();
  if(cpu_pic->base_isa() == _14BIT_E_PROCESSOR_)
  {
	cpu14e->status->put(cpu14e->status_shad.get());
	cpu14e->Wput(cpu14e->wreg_shad.get());
	cpu14e->bsr.put(cpu14e->bsr_shad.get());
	cpu14e->pclath->put(cpu14e->pclath_shad.get());
	cpu14e->ind0.fsrl.put(cpu14e->fsr0l_shad.get());
	cpu14e->ind0.fsrh.put(cpu14e->fsr0h_shad.get());
	cpu14e->ind1.fsrl.put(cpu14e->fsr1l_shad.get());
	cpu14e->ind1.fsrh.put(cpu14e->fsr1h_shad.get());
  }
}
