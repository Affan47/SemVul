getInternalTargets()
{
   ServiceTargetSearcher sts( getContainer(), ServiceTargetSearcher::checkRepair );
   sts.startSearch();

   internalTargets.clear();

   for ( ServiceTargetSearcher::Targets::const_iterator i = sts.getTargets().begin(); i != sts.getTargets().end(); ++i )
      if ( (*i)->getCarrier() == getContainer() ) {
         Vehicle* v = dynamic_cast<Vehicle*>(*i);
         if ( v )
            internalTargets.push_back( v );
      }

   return internalTargets;
}
