allServiceTypes()
{
   KServiceType::List result;
   const KSycocaEntry::List list = allEntries();
   for( KSycocaEntry::List::ConstIterator it = list.begin();
        it != list.end();
        ++it)
   {
      if ( (*it)->isType( KST_KServiceType ) ) {
          KServiceType::Ptr newServiceType = KServiceType::Ptr::staticCast( *it );
          result.append( newServiceType );
      }
   }
   return result;
}
