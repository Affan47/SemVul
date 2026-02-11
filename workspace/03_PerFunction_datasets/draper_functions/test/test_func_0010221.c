pex_add_remove (struct pex_obj *obj, const char *name, int allocated)
{
  char *add;

  ++obj->remove_count;
  obj->remove = XRESIZEVEC (char *, obj->remove, obj->remove_count);
  if (allocated)
    add = (char *) name;
  else
    add = xstrdup (name);
  obj->remove[obj->remove_count - 1] = add;
}
