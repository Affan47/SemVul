checkdone(ilocus, jlocus)
int ilocus, jlocus;
{
  int i, j;

  if (ilocus == locuslist1[0])
    return false;
  else {
    i = 0;
    do {
      i++;
    } while (jlocus != locuslist1[i - 1] && locuslist1[i - 1] != ilocus);
    j = 0;
    do {
      j++;
    } while (ilocus != locuslist2[j - 1] && j != nlocus2);
    return (locuslist1[i - 1] == jlocus && locuslist2[j - 1] == ilocus);
  }
}
