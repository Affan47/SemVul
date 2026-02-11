logMessage ( const ASCString& category, const ASCString& message )
{
   if ( MessagingHub::Instance().logCategoryEnabled( category ) )
      MessagingHub::Instance().logCategorizedMessage( category, message );
}
