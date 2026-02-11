draw_discrete (ModeInfo * mi)
{
  discretestruct *hp = &discretes[MI_SCREEN(mi)];
  int cycles = MI_CYCLES(mi);
  int i;

  if (hp->eraser) {
    hp->eraser = erase_window (MI_DISPLAY(mi), MI_WINDOW(mi), hp->eraser);
    return;
  }

  for (i = 0; i < 10; i++) {
    draw_discrete_1 (mi);
    hp->count++;
  }

  if (hp->count > cycles) {
    hp->eraser = erase_window (MI_DISPLAY(mi), MI_WINDOW(mi), hp->eraser);
    init_discrete(mi);
  }
}
