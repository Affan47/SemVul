gammapdf(const RowVector& vals, const float mu, const float var)
{
  RowVector res(vals);
  res=0;
  if((mu>0)&&(var>0.00001)){
    float a = std::pow(mu,2)/var;
    float b = mu/var;
    float c = lgam(a);
    if(std::abs(c) < 150){
      for (int mc=1; mc<=res.Ncols(); mc++){
	if(vals(mc)>0.000001){
	  res(mc) = std::exp(a*std::log(b) +
			     (a-1) * std::log(vals(mc))
			     - b*vals(mc) - c);
	}
      }
    }
  }
  res.Release();
  return res;
}
