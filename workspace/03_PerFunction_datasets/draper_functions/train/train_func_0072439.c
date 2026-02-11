count_sizety (NODE_T * p)
{
  if (p == NO_NODE) {
    return (0);
  } else if (IS (p, LONGETY)) {
    return (count_sizety (SUB (p)) + count_sizety (NEXT (p)));
  } else if (IS (p, SHORTETY)) {
    return (count_sizety (SUB (p)) + count_sizety (NEXT (p)));
  } else if (IS (p, LONG_SYMBOL)) {
    return (1);
  } else if (IS (p, SHORT_SYMBOL)) {
    return (-1);
  } else {
    return (0);
  }
}
