shootM2(HepRandomEngine* anEngine,
                                   double mean, double gamma, double cut )
{
   double rval, displ;
   double lower, upper, tmp;

   if ( gamma == 0.0 ) return mean;
   tmp = std::max(0.0,(mean-cut));
   lower = std::atan( (tmp*tmp-mean*mean)/(mean*gamma) );
   upper = std::atan( ((mean+cut)*(mean+cut)-mean*mean)/(mean*gamma) );
   rval = RandFlat::shoot(anEngine, lower, upper);
   displ = gamma*std::tan(rval);

   return std::sqrt( std::max(0.0, mean*mean+mean*displ) );
}
