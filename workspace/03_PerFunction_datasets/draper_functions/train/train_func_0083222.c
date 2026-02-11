graphics_scanline_do_partition(Graphics_scanline *line,int  start, int end) {
  Graphics_pointinfo *pivot;
  Graphics_pointinfo *cur;
  int pivotpos = start;
  int j;

  pivot = graphics_scanline_getpoint(line,end);
  for (j = start ; j < end ; j++) {
    cur = graphics_scanline_getpoint(line,j);
    if (cur->pos.x <= pivot->pos.x) {
      if (pivotpos != j) {
        graphics_scanline_swappoints(cur,
                                     graphics_scanline_getpoint(line,pivotpos));
      }
      pivotpos++;
    }
  }
  graphics_scanline_swappoints(pivot,graphics_scanline_getpoint(line,pivotpos));
  return pivotpos;
}
