runtime_initialize()
{
  if(cpu_pic->program_memory[PMindex+1])
    {
      word2_opcode = cpu_pic->program_memory[PMindex+1]->get_opcode();

      if((word2_opcode & 0xf000) != 0xf000)
	{
	  cout << "16bit-instructions.cc MOVSF error\n";
	  return;
	}

      cpu_pic->program_memory[PMindex+1]->update_line_number( file_id,  src_line, lst_line, 0, 0);
      destination = word2_opcode & ((opcode & 0x80) ? 0x7f : 0xfff);
      initialized = true;
    }

}
