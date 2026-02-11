module_list_globals(void) {
  LLVMModuleRef M = load_module();
  LLVMValueRef g;

  g = LLVMGetFirstGlobal(M);
  while (g) {
    LLVMTypeRef T = LLVMTypeOf(g);
    char *s = LLVMPrintTypeToString(T);

    printf("Global%s: %s %s\n",
           LLVMIsDeclaration(g) ? "Declaration" : "Definition",
           LLVMGetValueName(g), s);

    LLVMDisposeMessage(s);

    g = LLVMGetNextGlobal(g);
  }

  LLVMDisposeModule(M);

  return 0;
}
