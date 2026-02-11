returnHomopolymerA(int nMove, int** aanHA, int** aanMoves, int nI, int nJ, const char* acA, const char *acB)
{
  int retA = 0;

  switch(nMove){
  case DIAG:
    if(acA[nI - 1] == acB[nJ - 1]){
      if(getLastMatch(aanMoves[nI - 1][nJ - 1], nI - 1, nJ - 1, acA, acB) == acA[nI - 1]){
	retA = aanHA[nI - 1][nJ - 1] + 1;
      }
      else{
	retA = 1;
      }
    }
    else{
      retA = 0;
    }

    break;
  case LEFT:
    if(acB[nJ - 1] == getLastMatch(aanMoves[nI][nJ - 1], nI, nJ - 1, acA, acB)){
      retA = aanHA[nI][nJ - 1] + 1;
    }
    else{
      retA = 0;
    }
    break;

  case UP:

    if(acA[nI - 1] == getLastMatch(aanMoves[nI - 1][nJ], nI - 1, nJ, acA, acB)){
      retA = aanHA[nI - 1][nJ] + 1;
    }
    else{
      retA = 0;
    }
    break;
  }

  return retA;
}
