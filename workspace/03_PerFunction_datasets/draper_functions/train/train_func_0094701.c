THTensor_add(THTensor *tensor, double value)
{
  TH_TENSOR_APPLY(double, tensor, *tensor_p += value;);
}
