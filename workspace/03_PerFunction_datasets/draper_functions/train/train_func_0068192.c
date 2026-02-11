runOnFunction(Function &F) {
  Attribute A = F.getFnAttribute("ShaderType");

  unsigned ShaderType = ShaderType::COMPUTE;
  if (A.isStringAttribute()) {
    StringRef Str = A.getValueAsString();
    Str.getAsInteger(0, ShaderType);
  }
  if (ShaderType == ShaderType::COMPUTE)
    return false;

  visit(F);
  visit(F);

  return false;
}
