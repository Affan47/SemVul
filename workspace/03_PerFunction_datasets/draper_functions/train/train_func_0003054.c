start() {

  int n = _data.numExistingOutputFiles(_data._input._files);
  if (n > 0) {
    gtk_label_set_text(GTK_LABEL(_messageText), _("Output files exist, please delete them!"));
    return;
  }

  setBusy(true);
  _data.start(_data._input._files);
  _idleProcess = g_idle_add(&idleProcess, this);
}
