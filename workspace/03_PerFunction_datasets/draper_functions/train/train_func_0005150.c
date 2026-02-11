createList(intList *l){
  l->maxLen = DEF_LIST_SIZE;
  l->x = (unint*)calloc(DEF_LIST_SIZE, sizeof(*l->x));
  if(!l->x){
    printf("unable to alloc list, exiting\n");
    exit(1);
  }

  l->len = 0;
}
