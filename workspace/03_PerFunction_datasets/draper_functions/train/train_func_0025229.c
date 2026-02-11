new_choice_dlg(const ASCString& title, const ASCString& leftButton, const ASCString& rightButton )
{
   PG_Rect size = calcMessageBoxSize(title);
   MessageDialog msg( NULL, size,"", "", leftButton, rightButton, PG_Label::CENTER, "Window" );
   msg.getTextBox()->SetFontSize( msg.getTextBox()->GetFontSize() + 3 );
   msg.getTextBox()->SetText(title);
   msg.EnableDefaultKeys( false );

   msg.Show();

   return msg.RunModal();
}
