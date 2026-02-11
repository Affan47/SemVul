getLastMatch(int nMove, int nI, int nJ, const char *acA, const char *acB)
{
  switch(nMove){
  case DIAG:
    if(acA[nI - 1] == acB[nJ - 1]){
      return acA[nI - 1];
    }
    else{
      return '\0';
    }
    break;
  case LEFT:
    return acB[nJ - 1];
    break;
  case UP:
    return acA[nI - 1];
    break;
  }
}
