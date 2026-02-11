Pi_h_alpha(const baseFElement & K,KN_<double> & v) const
{
  const Triangle & T(K.T);

   for (int i=0,k=0;i<3;i++)
     {
        R2 E(T.Edge(i));
        R signe = &T[ (i+1)%3] < &T[ (i+2)%3] ? 1.0 : -1.0 ;
        v[k++]= signe*E.y;
        v[k++]=-signe*E.x;
     }
}
