arraySetMaxSize(TIntermSymbol *node, TType* type, int size, bool updateFlag, TSourceLoc line)
{
   bool builtIn = false;
   TSymbol* symbol = symbolTable.find(node->getSymbol(), &builtIn);
   if (symbol == 0)
   {
      error(line, " undeclared identifier", node->getSymbol().c_str(), "");
      return true;
   }
   TVariable* variable = static_cast<TVariable*>(symbol);

   type->setArrayInformationType(variable->getArrayInformationType());
   variable->updateArrayInformationType(type);


   if (!updateFlag)
      return false;

   size++;
   variable->getType().setMaxArraySize(size);
   type->setMaxArraySize(size);
   TType* tt = type;

   while (tt->getArrayInformationType() != 0)
   {
      tt = tt->getArrayInformationType();
      tt->setMaxArraySize(size);
   }

   return false;
}
