initMachine(int initialMemory, int *codes, int codeLength, int initPc) {
  Machine *m = (Machine*)malloc(sizeof(Machine));
  if (m != NULL) {
    m->stackPointer = 0;
    m->programCounter = initPc;
    m->halted = 0;
    m->memorySize = initialMemory;
    m->memory = (int*)malloc(initialMemory);
    if (m->memory == NULL) {
      free(m);
      return NULL;
    }
    m->opcode_funcs = &opcodeTable;
    m->programCodes = codes;
    m->programCodesCount = codeLength;
  }

  return m;
}
