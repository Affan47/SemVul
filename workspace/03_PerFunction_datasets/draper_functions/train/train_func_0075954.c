menu_blackp(GtkMenuItem *item, gpointer data) {
  Board *me;
  me=Board::PopupOwner;
  Board::PopupOwner = 0;
  if (!me) return;
  if (!me->mygame) return;
  if (!global.protocol) return;
  global.protocol->callPlayerAction(me->mygame->PlayerName[1],(string *) data);
}
