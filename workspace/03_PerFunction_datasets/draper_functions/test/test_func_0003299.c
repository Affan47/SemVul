getPackage( const ASCString& name ) const
{
   for ( PackageRepository::const_iterator p = packageRepository.begin(); p != packageRepository.end(); ++p )
      if ( (*p)->name.compare_ci( name ) == 0 )
         return *p;
   return NULL;
}
