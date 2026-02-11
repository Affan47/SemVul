get_points(double     number,
           const char *uval)
{
  if (!strcmp(uval, "mm"))
    return (number * 72.0 / 25.4);
  else if (!strcmp(uval, "cm"))
    return (number * 72.0 / 2.54);
  else if (!strcmp(uval, "in"))
    return (number * 72.0);
  else if (!strcmp(uval, "ft"))
    return (number * 72.0 * 12.0);
  else if (!strcmp(uval, "m"))
    return (number * 72.0 / 0.0254);
  else
    return (number);
}
