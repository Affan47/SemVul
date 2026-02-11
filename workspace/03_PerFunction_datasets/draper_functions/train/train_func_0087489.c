Hlsl2Glsl_Initialize()
{
   TInfoSink infoSink;

   if (!InitProcess())
      return 0;

   if (!PerProcessGPA)
   {
      TPoolAllocator *builtInPoolAllocator = new TPoolAllocator();
      builtInPoolAllocator->push();
      TPoolAllocator* gPoolAllocator = &GlobalPoolAllocator;
      SetGlobalPoolAllocatorPtr(builtInPoolAllocator);

      TSymbolTable symTables[EShLangCount];
      GenerateBuiltInSymbolTable(infoSink, symTables, EShLangCount);

      PerProcessGPA = new TPoolAllocator();
      PerProcessGPA->push();
      SetGlobalPoolAllocatorPtr(PerProcessGPA);

      SymbolTables[EShLangVertex].copyTable(symTables[EShLangVertex]);
      SymbolTables[EShLangFragment].copyTable(symTables[EShLangFragment]);

      SetGlobalPoolAllocatorPtr(gPoolAllocator);

      symTables[EShLangVertex].pop();
      symTables[EShLangFragment].pop();

      builtInPoolAllocator->popAll();
      delete builtInPoolAllocator;

   }

   return 1;
}
