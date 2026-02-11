redo( const Context& context )
{
   if ( getState() == Finished || getState() == Run )
      setState( SetUp );

   deleteChildren();

   Context c ( context, this );

   return go(c);
}
