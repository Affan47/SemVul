edfplus_annotation_add_copy(struct annotationblock **list, struct annotationblock *annotation)
{
  struct annotationblock *annotlist, *new_annot;

  annotlist = *list;

  new_annot = (struct annotationblock *)calloc(1, sizeof(struct annotationblock));
  if(new_annot == NULL)
  {
    return;
  }

  memcpy(new_annot, annotation, sizeof(struct annotationblock));

  new_annot->next_annotation = NULL;

  if(annotlist == NULL)
  {
    new_annot->former_annotation = NULL;

    *list = new_annot;

    return;
  }

  while(annotlist->next_annotation != NULL)
  {
    annotlist = annotlist->next_annotation;
  }

  annotlist->next_annotation = new_annot;

  new_annot->former_annotation = annotlist;
}
