Monitor_InstructionDI(long FromPC, char *buffer)
{
	unsigned long Value;
	long x;
	long OldPC;
	char InstrStr[16];
	char Arg1[32];
	char Arg2[32];
	struct _Instruction *InstructionPtr;

	buffer[0]=0;


	OldPC=memory_core.pc;
	memory_core.pc=FromPC;


	Memory_RetrWord(&Value, memory_core.pc);
	buffer+=sprintf(buffer,"%08lX: ", memory_core.pc);

	InstructionPtr=Instruction_FindInstruction(Value);

	if(InstructionPtr==NULL) {
		memory_core.pc+=2;
	} else {

		(*InstructionPtr->DIFunctionPtr)(&InstrStr[0], &Arg1[0], &Arg2[0]);

		for(x=FromPC;x<FromPC+8;x+=2) {
			if(x < memory_core.pc) {
				Memory_RetrWord(&Value, x);
				buffer+=sprintf(buffer,"%04hX ", (unsigned short)Value);
			} else
				buffer+=sprintf(buffer,"     ");
		}

		buffer+=sprintf(buffer," %-9s ", &InstrStr[0]);
		if(Arg1[0]) buffer+=sprintf(buffer,"%s", &Arg1[0]);
		if(Arg2[0]) buffer+=sprintf(buffer,",%s", &Arg2[0]);
	}

	x = memory_core.pc - FromPC;

	memory_core.pc=OldPC;
	return x;
}
