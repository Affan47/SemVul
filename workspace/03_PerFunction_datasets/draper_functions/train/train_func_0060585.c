Build(Real* probs)
{
   int i;
   dg=new DiscreteGen(n,probs);
   if (!dg) ErrorNoSpace();
   mean=0.0; var=0.0;
   for (i=0; i<n; i++) mean = mean + (rv[i])->Mean()*probs[i];
   for (i=0; i<n; i++)
   {
      ExtReal sigsq=(rv[i])->Variance();
      ExtReal mudif=(rv[i])->Mean()-mean;
      var = var + (sigsq+square(mudif))*probs[i];
   }

}
