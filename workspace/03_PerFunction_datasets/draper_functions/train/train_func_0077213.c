disable ( void )
{
   if ( status != off ) {
      if ( status != init1a && status != init2 && !unit->typ->hasFunction(ContainerBaseType::MoveWithReactionFire)  ) {
          unit->setMovement ( 0, 0 );
       }
       status = off;
   }
}
