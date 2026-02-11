disasm16 (pic_processor *cpu, unsigned int address, unsigned int inst)
{
  instruction *pi;

  cpu16->setCurrentDisasmAddress(address);

  pi = 0;
  for(int i =0; i<NUM_OP_18CXX && !pi; i++)
    if((op_18cxx[i].inst_mask & inst) == op_18cxx[i].opcode)
      pi = op_18cxx[i].inst_constructor(cpu, inst,address);

  if(pi == 0)
    pi = invalid_instruction::construct(cpu, inst, address);

  return (pi);
}
