setMAXDYN(double value)
{
    if (value > 1.0) {
    MAXDYN = value;
  }
  else {
    printf("### WARNING: CglRedSplit2::setMAXDYN(): value: %f ignored\n",
	   value);
  }
}
