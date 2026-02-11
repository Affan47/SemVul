MarkVariableAsUsed(const char* var)
{
  this->Internal->VarUsageStack.top().insert(var);
}
