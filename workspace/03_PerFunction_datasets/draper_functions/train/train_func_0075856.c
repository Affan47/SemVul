AddExpression(const char* expr)
{
  this->Internals->Expressions.push_back(
    kwsys::RegularExpression(
      this->PatternToRegex(expr).c_str()));
}
