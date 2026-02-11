p_flat(Flat f)
{
  while (f != NULL) {
    printf("%s", VARIABLE(f->t) ? "*" : sn_to_str(SYMNUM(f->t)));
    if (f->place_holder)
      printf("[]");
    f = f->next;
    if (f != NULL)
      printf("-");
  }
  printf("\n");
}
