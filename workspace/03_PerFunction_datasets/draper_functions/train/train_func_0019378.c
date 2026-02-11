doDistribution(int n_,int *distrib_,int loc_,int span_,
				     MSLayoutVector *vec_,int size_,int spacing_)
{
  int diff,amt,i,sum=0;

  for (i=loc_;i<loc_+span_;i++) sum+=vec_[i].value();
  if (span_>1)  sum+=(span_-1)*spacing_;
  diff=size_-sum;
  if (diff>0&&n_>0)
   {

     amt=diff/n_;
     for (i=0;i<n_-1;i++)
      {
	vec_[distrib_[i]]._value+=amt;
	diff-=amt;
      }

     vec_[distrib_[i]]._value+=diff;
   }
}
