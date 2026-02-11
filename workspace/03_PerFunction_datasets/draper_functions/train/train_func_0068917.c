resource(const ContainerBase* c, bool recurse )
{
   Resources res = c->baseType->productionCost;
   for ( int r = 0; r < 3; ++r )
      res.resource(r) += c->getAvailableResource( maxint, r, 0 );

   if ( recurse )
   for ( ContainerBase::Cargo::const_iterator i = c->getCargo().begin(); i != c->getCargo().end(); ++i )
      if ( *i )
         res += resource(*i, recurse);

   return res;
}
