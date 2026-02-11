extensionSet(void (FOTBuilder::*func)(bool), bool arg)
{
  (this->*func)(arg);
}
