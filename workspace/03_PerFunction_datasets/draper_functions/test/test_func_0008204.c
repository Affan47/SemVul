put ( std::ostream& os ) const
{
   char beginMarker[] = "DRand48Engine-begin";
   os << beginMarker << "\nUvec\n";
   std::vector<unsigned long> v = put();
   for (unsigned int i=0; i<v.size(); ++i) {
     os <<  v[i] <<  "\n";
   }
  return os;

#ifdef REMOVED
   unsigned short dummy[] = { 0, 0, 0 };
   unsigned short* cseed = seed48(dummy);
   char endMarker[] = "DRand48Engine-end";
   os << " " << beginMarker << " ";
   os << theSeed << " ";
   for (int i=0; i<3; ++i) {
     dummy[i] = cseed[i];
     os << cseed[i] << " ";
   }
   os << endMarker << " ";
   seed48(dummy);
   return os;
#endif
}
