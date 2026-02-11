GetRangeValue(double rangeMin,
                                                       double rangeMax)
{
  double result;
  if(rangeMin==rangeMax)
    {
    result=rangeMin;
    }
  else
    {
    result=rangeMin+this->GetValue()*(rangeMax-rangeMin);
    }
  assert("post: valid_result" &&
         ((rangeMin<=rangeMax && result>=rangeMin && result<=rangeMax)
          || (rangeMax<=rangeMin && result>=rangeMax && result<=rangeMin)));
  return result;
}
