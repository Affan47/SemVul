add_element (PlyFile *plyfile, char **words, int)
{
  PlyElement *elem;


  elem = (PlyElement *) myalloc (sizeof (PlyElement));
  elem->name = strdup (words[1]);
  elem->num = atoi (words[2]);
  elem->nprops = 0;


  if (plyfile->nelems == 0)
    plyfile->elems = (PlyElement **) myalloc (sizeof (PlyElement *));
  else
    plyfile->elems = (PlyElement **) realloc (plyfile->elems,
                     sizeof (PlyElement *) * (plyfile->nelems + 1));


  plyfile->elems[plyfile->nelems] = elem;
  plyfile->nelems++;
}
