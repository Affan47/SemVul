Dignify(obj, sign)
int obj, sign;
{
  if (obj > oNorm)
    return ' ';
  if (ruler1[obj] == sign || ruler2[obj] == sign)
    return 'R';
  if (ruler1[obj] == Mod12(sign+6) || ruler2[obj] == Mod12(sign+6))
    return 'F';
  if (exalt[obj] == sign)
    return 'e';
  if (exalt[obj] == Mod12(sign+6))
    return 'd';
  return '-';
}
