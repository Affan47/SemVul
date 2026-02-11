cdk_strlist_free (cdk_strlist_t sl)
{
  cdk_strlist_t sl2;

  for (; sl; sl = sl2)
    {
      sl2 = sl->next;
      cdk_free (sl);
    }
}
