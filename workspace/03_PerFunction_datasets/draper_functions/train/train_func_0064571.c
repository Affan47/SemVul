remove_gui_layer(struct gui_layer *gui_layer)
{
  int i;

  for(i = 0; i < Main.guis_count - 1; i++) {
    if(Main.guis[i] && (Main.guis[i]== gui_layer)) {
      gui_layer_destroy(&Main.guis[i]);
      Main.guis[i] = Main.guis[i + 1];
      Main.guis[i + 1] = NULL;
    } else {
      if(!Main.guis[i]) {
	Main.guis[i] = Main.guis[i + 1];
        Main.guis[i + 1] = NULL;
      }
    }
  }

  if (Main.guis[Main.guis_count - 1]) {
    gui_layer_destroy(&Main.guis[Main.guis_count - 1]);
  }
}
