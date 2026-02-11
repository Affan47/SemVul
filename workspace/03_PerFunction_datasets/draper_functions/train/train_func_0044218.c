extraRowSpace(int num_,MSLayoutVector *vec_,int size_)
{
  if (num_>0)
   {
     int sum=0;
     for (unsigned i=0;i<num_;i++) sum+=vec_[i].value();
     int diff=size_-sum;

     if (diff>0) vec_[num_-1]._value+=diff;
     else if (diff<0)
      {
        diff=sum-size_;
        vec_[num_-1]._value-=diff;
      }
   }
}
