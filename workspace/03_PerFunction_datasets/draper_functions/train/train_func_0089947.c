setSkipGomory(int value)
{
  if (value >= 0 && value <= 1){
    skipGomory_ = value;
  }
  else{
    printf("### WARNING: CglRedSplit2Param::skipGomory(): value: %d ignored\n",
	   value);
  }
}
