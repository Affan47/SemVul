trace() const {
   double t = 0.0;
   for (mcIter d = m.begin(); d < m.end(); d += (ncol+1) )
      t += *d;
   return t;
}
