getfen_ok(GtkWidget *w, gpointer data) {
  string s;
  GetFENDialog *me;
  me=(GetFENDialog *)data;
  s=gtk_entry_get_text(GTK_ENTRY(me->e));
  me->owner->applyFEN(s);
  me->release();
}
