all()
{
   for ( int i = 0; i < listbox->GetWidgetCount(); ++i ) {
      PG_ListBoxBaseItem* bi = dynamic_cast<PG_ListBoxBaseItem*>(listbox->FindWidget(i));
      if ( bi )
         bi->Select( true );
   }
   listbox->Update();
   return true;
}
