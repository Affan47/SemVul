GetScaleModeAsString(void)
{
  if ( this->ScaleMode == SCALE_BY_MAGNITUDE)
    {
    return "ScaleByMagnitude";
    }
  else if ( this->ScaleMode == SCALE_BY_COMPONENTS)
    {
    return "ScaleByVectorComponents";
    }

  return "NoDataScaling";
}
