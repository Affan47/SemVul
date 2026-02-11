injectInput() {
  char z[4096],y[256];
  int id;

  g_strlcpy(z,gtk_entry_get_text(GTK_ENTRY(inputbox)),4096);

  if (ims->getSearchMode()) {
    inconsole->SearchString = z;
    inconsole->execSearch();
    ims->setSearchMode(false);
    goto ii_nothing_else;
  }

  if (asetprefix.match(z)) {
    id=notebook->getCurrentPageId();
    imscache.set(id, asetprefix.getStarToken(0) );
    ims->setPrefix( * (imscache.get(id)) );
    goto ii_nothing_else;
  }

  if (arunscript.match(z)) {
    g_strlcpy(y,arunscript.getStarToken(0),256);
    new ScriptInstance(y);
    goto ii_nothing_else;
    return;
  }

  if (ims->getChatMode()) {
    g_strlcpy(z,ims->getPrefix().c_str(),4096);
    if (z[0])
      g_strlcat(z," ",4096);
  } else
    z[0]=0;
  g_strlcat(z,gtk_entry_get_text(GTK_ENTRY(inputbox)),4096);

  userInput(z);

 ii_nothing_else:
  gtk_entry_set_text(GTK_ENTRY(inputbox),"\0");
}
