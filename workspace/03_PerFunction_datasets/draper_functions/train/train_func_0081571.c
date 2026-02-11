takeQString (struct qstring *str)
{
  char *res = str->str;
  if (str->prev != NULL)
    {
      str->prev->next = str->next;
    }
  else
    {
      qstringList = str->next;
    }
  if (str->next != NULL)
    {
      str->next->prev = (str->prev);
    }
  free (str);
  return res;
}
