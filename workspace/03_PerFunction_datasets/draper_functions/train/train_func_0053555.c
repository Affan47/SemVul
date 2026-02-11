breakProcess(MSIndexVector& i_)
{
  MSString buffer;
  MSInt aInt((int)(MSIndexedFunctions::computeIndexedFunction(vector(),weights(),i_,breakProcessMode())));
  breakString()<<aInt.format(buffer,format());
}
