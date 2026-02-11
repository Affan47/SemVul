editString2( const ASCString& title, const ASCString& defaultValue )
{
   StringEditor se ( title, defaultValue );
   se.Show();
   se.RunModal();
   return se.GetEditedText();
}
