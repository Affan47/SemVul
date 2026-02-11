event_broken(type, n)
int type, n;
{
  int i;

  if (type == GT) {
    for (i=0; i<n; i++) {
      emit_char('>');
    };
  } else {
    for (i=0; i<n; i++) {
      emit_char('<');
    };
  };
}
