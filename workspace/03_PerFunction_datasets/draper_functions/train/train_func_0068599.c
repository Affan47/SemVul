File2Chin(uint32_t dwFileStr, int sdPlayer) {
  int nPos;
  char *lpArg;
  union {
    uint16_t w[4];
    uint64_t qw;
  } Ret;

  lpArg = (char *) &dwFileStr;
  nPos = Byte2Direct(lpArg[0]);
  if (nPos == MAX_DIRECT) {
    nPos = Byte2Pos(lpArg[1]);
    Ret.w[0] = (nPos == MAX_POS ? lpcwPiece2Word[sdPlayer][Byte2Piece(lpArg[0])] : lpcwPos2Word[nPos]);
    Ret.w[1] = (nPos == MAX_POS ? lpcwDigit2Word[sdPlayer][Byte2Digit(lpArg[1])] :
        lpcwPiece2Word[sdPlayer][Byte2Piece(lpArg[0])]);
  } else {
    Ret.w[0] = lpcwPos2Word[nPos + DIRECT_TO_POS];
    Ret.w[1] = lpcwPiece2Word[sdPlayer][Byte2Piece(lpArg[1])];
  }
  if (lpArg[2] == '=' && Byte2Piece(lpArg[3]) == 6) {
    Ret.w[2] = wPromote;
    Ret.w[3] = lpcwPiece2Word[sdPlayer][6];
  } else {
    Ret.w[2] = lpcwDirect2Word[Byte2Direct(lpArg[2])];
    Ret.w[3] = lpcwDigit2Word[sdPlayer][Byte2Digit(lpArg[3])];
  }
  return Ret.qw;
}
