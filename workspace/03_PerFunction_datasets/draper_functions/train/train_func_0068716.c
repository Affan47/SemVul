set_color(Node* n, unsigned int color) {
   if(_colors == NULL) {
      _colors = new ColorMap();
   }
   (*_colors)[n] = color;
}
