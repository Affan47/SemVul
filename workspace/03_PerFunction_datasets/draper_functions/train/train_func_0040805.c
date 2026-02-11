functionella(char const *a, char const *b)
{
  if (!a &&  b)
    throw "a is no good";
  if ( a && !b)
    throw "b is no better";
  if (!a && !b)
    throw bizop();

  return *a - *b;
}
