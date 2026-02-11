ui_init(struct state *s, struct ui *ui) {

  ui->cursor.i = s->grid.width/2;
  ui->cursor.j = s->grid.height/2;
  int i, j;
  for (i=0; i<s->grid.width; ++i) {
    for (j=0; j<s->grid.height; ++j) {
      if (s->grid.tiles[i][j].units[s->controlled][citizen] >
          s->grid.tiles[ui->cursor.i][ui->cursor.j].units[s->controlled][citizen]) {
        ui->cursor.i = i;
        ui->cursor.j = j;
      }
    }
  }

  ui->xskip = MAX_WIDTH * 2 + 1;
  for(i=0; i<s->grid.width; ++i)
    for(j=0; j<s->grid.height; ++j)
      if(is_visible(s->grid.tiles[i][j].cl)) {
        int x = i*2 + j;
        if (ui->xskip > x)
          ui->xskip = x;
      }
  ui->xskip = ui->xskip/2;
}
