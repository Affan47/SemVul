create_sheet_entry(GtkSheet *sheet)
{
 GtkWidget *widget;
 GtkWidget *parent;
 GtkWidget *entry;
 GtkStyle *style;
 gint found_entry = FALSE;

 widget = GTK_WIDGET(sheet);

 style = gtk_style_copy(GTK_WIDGET(sheet)->style);

 if(sheet->sheet_entry){

    gtk_widget_ref(sheet->sheet_entry);
    gtk_widget_unparent(sheet->sheet_entry);
    gtk_widget_destroy(sheet->sheet_entry);
 }

 if(sheet->entry_type){

   if(!gtk_type_is_a (sheet->entry_type, GTK_TYPE_ENTRY)){

     parent = GTK_WIDGET(gtk_type_new(sheet->entry_type));

     sheet->sheet_entry = parent;

     entry = gtk_sheet_get_entry (sheet);
     if(GTK_IS_ENTRY(entry)) found_entry = TRUE;

   } else {

     parent = GTK_WIDGET(gtk_type_new(sheet->entry_type));
     entry = parent;
     found_entry = TRUE;

   }

   if(!found_entry){

     g_warning ("Entry type must be GtkEntry subclass, using default");
     entry = gtk_entry_new ();
     sheet->sheet_entry = entry;

   } else {

     sheet->sheet_entry = parent;

   }


 } else {

     entry = gtk_entry_new ();
     sheet->sheet_entry = entry;

 }

 gtk_widget_size_request(sheet->sheet_entry, NULL);

 if(GTK_WIDGET_REALIZED(sheet))
   {
      gtk_widget_set_parent_window (sheet->sheet_entry, sheet->sheet_window);
      gtk_widget_set_parent(sheet->sheet_entry, GTK_WIDGET(sheet));
      gtk_widget_realize(sheet->sheet_entry);
   }


 gtk_signal_connect_object(GTK_OBJECT(entry),"key_press_event",
                           (GtkSignalFunc) gtk_sheet_key_press,
                           GTK_OBJECT(sheet));


 gtk_widget_show (sheet->sheet_entry);
}
