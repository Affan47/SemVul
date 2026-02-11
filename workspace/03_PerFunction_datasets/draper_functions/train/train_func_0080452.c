init() {
  try {
    liesPreferences();
  } catch (Fehler f) {
    print_to_stderr(_("Error reading preferences file '.cuyo':\n"));
    print_to_stderr(f.getText()+"\n");
    exit(1);
  }
}
