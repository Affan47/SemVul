debugdlg_writecons(GtkWidget *w, gpointer data) {
    DebugDialog *me;
    tstring t;
    string *c;
    char z[512];

    me = (DebugDialog *) data;
    t.set(me->pipedata);
    global.output->append("=== START DEBUG INFO ===",0xc0ff00);
    while( (c=t.token("\n")) != 0) {
      memset(z,0,512);
      c->copy(z,511);
      global.output->append(z, global.Colors.TextBright);
    }
    global.output->append("=== END DEBUG INFO ===",0xc0ff00);
  }
