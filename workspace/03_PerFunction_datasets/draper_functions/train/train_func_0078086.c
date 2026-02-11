object_list_symbols(void) {
  LLVMMemoryBufferRef MB;
  LLVMObjectFileRef O;
  LLVMSectionIteratorRef sect;
  LLVMSymbolIteratorRef sym;
  char *msg = NULL;

  if (LLVMCreateMemoryBufferWithSTDIN(&MB, &msg)) {
    fprintf(stderr, "Error reading file: %s\n", msg);
    exit(1);
  }

  O = LLVMCreateObjectFile(MB);
  if (!O) {
    fprintf(stderr, "Error reading object\n");
    exit(1);
  }

  sect = LLVMGetSections(O);
  sym = LLVMGetSymbols(O);
  while (!LLVMIsSymbolIteratorAtEnd(O, sym)) {

    LLVMMoveToContainingSection(sect, sym);
    printf("%s @0x%08" PRIx64 " +%" PRIu64 " (%s)\n", LLVMGetSymbolName(sym),
           LLVMGetSymbolAddress(sym), LLVMGetSymbolSize(sym),
           LLVMGetSectionName(sect));

    LLVMMoveToNextSymbol(sym);
  }

  LLVMDisposeSymbolIterator(sym);

  LLVMDisposeObjectFile(O);

  return 0;
}
