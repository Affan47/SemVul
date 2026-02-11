SoundEventChanged() {
  int i;
  for(i=0;i<N_SOUND_EVENTS;i++) {
    gtk_label_set_text(GTK_LABEL(sndd[i]), sndcopy[i].getDescription());
    gtk_widget_queue_resize(sndd[i]);
  }
}
