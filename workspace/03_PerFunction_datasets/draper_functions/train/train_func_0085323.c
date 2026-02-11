m68k_execute(int num_cycles)
{

	if(!CPU_STOPPED)
	{

		SET_CYCLES(num_cycles);
		m68ki_initial_cycles = num_cycles;


		USE_CYCLES(CPU_INT_CYCLES);
		CPU_INT_CYCLES = 0;


		m68ki_set_address_error_trap();


		do
		{

			m68ki_trace_t1();


			m68ki_use_data_space();


			m68ki_instr_hook();


			REG_PPC = REG_PC;


			REG_IR = m68ki_read_imm_16();
			m68ki_instruction_jump_table[REG_IR]();
			USE_CYCLES(CYC_INSTRUCTION[REG_IR]);


			m68ki_exception_if_trace();
		} while(GET_CYCLES() > 0);


		REG_PPC = REG_PC;


		USE_CYCLES(CPU_INT_CYCLES);
		CPU_INT_CYCLES = 0;


		return m68ki_initial_cycles - GET_CYCLES();
	}


	SET_CYCLES(0);
	CPU_INT_CYCLES = 0;

	return num_cycles;
}
