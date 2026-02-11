event_tempo(n, a, b, rel, pre, post)


int n;
int a, b, rel;
char *pre;
char *post;
{
  int t_num, t_denom;
  int new_div;
  long new_tempo;
  int tempo_l, tempo_h;

  if ((n == 0) || ((a!=0) && (b == 0))) {
    event_error("malformed Q: field ignored");
  } else {
    if (dotune) {
      if (pastheader) {
        tempo_num = a;
        tempo_denom = b;
        relative_tempo = rel;
        tempounits(&t_num, &t_denom);
        new_tempo = (long) 60*1000000*t_denom/(n*4*t_num);

        tempo_l = new_tempo & 0xffff;
        tempo_h = new_tempo >> 16;
        new_div = (int) ((float)DIV*(float)new_tempo/(float)tempo + 0.5);
        addfeature(TEMPO, new_div, tempo_h, tempo_l);
      } else {
        Qtempo = n;
        tempo_num = a;
        tempo_denom = b;
        relative_tempo = rel;
      };
    };
  };
}
