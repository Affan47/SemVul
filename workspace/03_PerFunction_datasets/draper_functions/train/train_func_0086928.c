addNumRowsReduction(int value)
{
  if (value >= 0) {
    numRowsReduction_.push_back(value);
  }
  else {
    printf("### WARNING: CglRedSplit2Param::addNumRowsReduction(): value: %d ignored\n",
	   value);
  }
}
