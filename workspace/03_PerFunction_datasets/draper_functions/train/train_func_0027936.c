printList(intList *l){
  unint i;
  printf("len= %d maxLen= %d\n",l->len,l->maxLen);
  for(i=0;i<l->len;i++)
    printf("%d ",l->x[i]);
  printf("\n");
}
