printModuleTypes() {
  Out << "/* Helper union for bitcasts */\n";
  Out << "typedef union {\n";
  Out << "  unsigned int Int32;\n";
  Out << "  unsigned long long Int64;\n";
  Out << "  float Float;\n";
  Out << "  double Double;\n";
  Out << "} llvmBitCastUnion;\n";


  std::vector<StructType*> StructTypes;
  TheModule->findUsedStructTypes(StructTypes);

  if (StructTypes.empty()) return;

  Out << "/* Structure forward decls */\n";

  unsigned NextTypeID = 0;


  for (unsigned i = 0, e = StructTypes.size(); i != e; ++i) {
    StructType *ST = StructTypes[i];

    if (ST->isLiteral() || ST->getName().empty())
      UnnamedStructIDs[ST] = NextTypeID++;

    std::string Name = getStructName(ST);

    Out << "typedef struct " << Name << ' ' << Name << ";\n";
  }

  Out << '\n';


  SmallPtrSet<Type *, 16> StructPrinted;


  Out << "/* Structure contents */\n";
  for (unsigned i = 0, e = StructTypes.size(); i != e; ++i)
    if (StructTypes[i]->isStructTy())

      printContainedStructs(StructTypes[i], StructPrinted);
}
