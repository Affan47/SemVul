innards(int X, int Y, int data[][3], int n){
    for (int i = 0; i < n; i++) {
      fl_color((Fl_Color)(i < n-1 ? data[i][2] : labelcolor()));
      fl_draw(rt_angle,rt_text, X+data[i][0], Y+data[i][1]);
    }
  }
