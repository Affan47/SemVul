set_profile_start_break(Processor *cpu,
					 unsigned int address,
					 TriggerObject *f1)
{
  Profile_Start_Instruction *psi = new Profile_Start_Instruction(cpu,address,0,f1);

  return bp.set_breakpoint(psi,cpu);

}
