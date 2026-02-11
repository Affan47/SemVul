getNum(void) const
{
  if (PRIVATE(this)->numNormals == 0 && PRIVATE(this)->normalData.generator) {
    return PRIVATE(this)->normalData.generator->getNumNormals();
  }
  return PRIVATE(this)->numNormals;
}
