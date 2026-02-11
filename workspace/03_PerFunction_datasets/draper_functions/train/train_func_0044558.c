findDiff(char a, char b)
{
  int diff;

  if(a < b) swap(a,b);

  if(b == 32 && (a >= '0' && a <= '9'))
    diff = abs(b-a)-15;
  else if(b == 32 && (a >= 'A' && a <= 'Z'))
    diff = abs(b-a)-22;
  else if(b == 32 && (a >= 'a' && a <= 'z'))
    diff= abs(b-a)-28;
  else if((b >= '0' && b <= '9') && (a >= 'A' && a <= 'Z'))
    diff = abs(b-a)-7;
  else if((b >= '0' && b <= '9') && (a >= 'a' && a <= 'z'))
    diff = abs(b-a)-13;
  else if((b >= 'A' && b <= 'Z') && (a >= 'a' && a <= 'z'))
    diff = abs(b-a)-6;
  else
    diff = abs(b-a);

  return diff;
}
