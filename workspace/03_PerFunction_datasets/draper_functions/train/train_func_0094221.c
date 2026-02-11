setAttacked()
{
   attacked = true;
   for ( Cargo::iterator i = cargo.begin(); i != cargo.end(); ++i )
      if ( *i )
         (*i)->setAttacked();
}
