p2ppad_accept(GtkWidget *w, gpointer data) {
  P2PPad *me = (P2PPad *) data;
  if (global.protocol)
    me->proto->acceptProposal();
  me->clearProposal();
}
