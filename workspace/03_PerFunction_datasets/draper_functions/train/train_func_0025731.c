defend_both(int astr, int bstr)
{
  int a_threatened = 0;
  int b_threatened = 0;
  int a_savepos;
  int b_savepos;
  int acode = 0;
  int dcode = 0;

  int color = board[astr];
  ASSERT1(IS_STONE(color) , astr);
  ASSERT1(color == board[bstr], bstr);


  if (countlib(astr) > countlib(bstr)) {
    int t = astr;
    astr = bstr;
    bstr = t;
  }

  attack_and_defend(astr, &acode, NULL, &dcode, &a_savepos);
  if (acode != 0) {
    a_threatened = 1;
    if (dcode != WIN)
      return 0;
  }

  attack_and_defend(bstr, &acode, NULL, &dcode, &b_savepos);
  if (acode != 0) {
    b_threatened = 1;
    if (dcode != WIN)
      return 0;
  }


  if (!a_threatened || !b_threatened)
    return WIN;


  if (a_savepos == b_savepos)
    return WIN;


  if (trymove(a_savepos, color, "defend_both-A", astr)) {
    if (board[bstr] && !attack(bstr, NULL)) {
      popgo();
      return WIN;
    }
    popgo();
  }

  if (trymove(b_savepos, color, "defend_both-B", bstr)) {
    if (board[astr] && !attack(astr, NULL)) {
      popgo();
      return WIN;
    }
    popgo();
  }


  {
    int adjs1[MAXCHAIN];
    int neighbors1;
    int adjs2[MAXCHAIN];
    int neighbors2;
    int r;
    int s;
    int epos;
    int fpos;

    neighbors1 = chainlinks(astr, adjs1);
    neighbors2 = chainlinks(bstr, adjs2);

    for (r = 0; r < neighbors1; r++) {
      epos = adjs1[r];
      if (countlib(epos) <= 4
	  && (epos != a_savepos)
	  && (epos != b_savepos)) {

	for (s = 0; s < neighbors2; s++) {
	  if (adjs2[s] == adjs1[r])
	    break;
	}
	if (s == neighbors2)
	  continue;

	if (attack(epos, &fpos)) {
	  if (trymove(fpos, color, "defend_both-C", astr)) {
	    if (board[astr] && board[bstr]
		&& !attack(astr, NULL)
		&& !attack(bstr, NULL)) {
	      popgo();
	      return WIN;
	    }
	    popgo();
	  }
	}
      }
    }
  }


  return 0;
}
