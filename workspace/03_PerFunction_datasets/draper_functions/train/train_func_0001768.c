runtime_initialize()
{
  if(cpu_pic->program_memory[PMindex+1])
    {
      word2_opcode = cpu_pic->program_memory[PMindex+1]->get_opcode();

      if((word2_opcode & 0xff00) != 0xf000)
	{
	  cout << "16bit-instructions.cc LFSR error\n";
	  return;
	}

      cpu_pic->program_memory[PMindex+1]->update_line_number( file_id,  src_line, lst_line, 0, 0);
      k = ( (opcode & 0xf)<<8) | (word2_opcode & 0xff);
      initialized = true;
    }

}
