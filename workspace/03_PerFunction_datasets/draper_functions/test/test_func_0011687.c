GetShaderVariableSize(const char* name)
{
  if (!this->HasShaderVariable(name))
    {
    return 0;
    }
  return this->Internals->UniformVariables[name].GetNumberOfValues();
}
