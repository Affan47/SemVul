listTriggeredTechAdapter() const
{
   ASCString s;
   for ( TriggeredTechAdapter::const_iterator i = triggeredTechAdapter.begin(); i != triggeredTechAdapter.end(); ++i ) {
      s += "#fontsize=14# ";
      s += *i + "\n";
      s += "#fontsize=10#";
      int counter = 0;
      for ( TechAdapterContainer::iterator j = techAdapterContainer.begin(); j != techAdapterContainer.end(); ++j ) {
         if ( (*j)->getName() == *i ) {
            if ( counter )
               s += " ----\n";
            ++counter;

            s += (*j)->techDependency.showDebug( *this );
         }
      }
      s += "#fontsize=14#\n";


   }

   return s;
}
