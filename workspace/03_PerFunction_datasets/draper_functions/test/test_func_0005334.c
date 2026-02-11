getTypeInfoDeclaration (void)
{
  if (sym->isInterfaceDeclaration())
    return new TypeInfoInterfaceDeclaration (this);
  else
    return new TypeInfoClassDeclaration (this);
}
