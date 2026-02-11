combo_box_changed_cb( GtkComboBoxEntry* widget, gpointer data ) {


  Ink_ComboBoxEntry_Action *act = INK_COMBOBOXENTRY_ACTION( data );


  gint newActive = gtk_combo_box_get_active( GTK_COMBO_BOX( widget ));
  if( newActive >= 0 ) {

    if( newActive != act->active ) {
      act->active = newActive;
      g_free( act->text );
      act->text = gtk_combo_box_get_active_text( GTK_COMBO_BOX( widget ));


      g_signal_emit( G_OBJECT(act), signals[CHANGED], 0 );

    }
  }
}
