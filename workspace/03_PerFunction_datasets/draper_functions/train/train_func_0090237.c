jni(void)	 	 { UINT8 i=M_RDMEM_OPCODE(); if (R.irq_state == I8039_EXTERNAL_INT) { R.PC.w.l = ((R.PC.w.l-1) & 0xf00) | i; } else ADJUST_CYCLES }
