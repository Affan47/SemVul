i2list_multisubset(I2list a, I2list b)
{
  if (a == NULL)
    return TRUE;
  else if (!i2list_multimember(b, a->i, a->j))
    return FALSE;
  else
    return i2list_multisubset(a->next, b);
}
