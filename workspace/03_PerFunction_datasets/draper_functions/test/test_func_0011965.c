butTblock_guessH(ButEnv *env, const char *text, int w, int fontNum)  {
  int  curW = 0, curH;
  int  wLastSpace = 0;
  int  fontH;
  int  i;

  fontH = butEnv_fontH(env, fontNum);
  curH = fontH;
  for (i = 0;  text[i];  ++i)  {
    if (text[i] == ' ')  {
      curW += butEnv_charWidth(env, text+i, fontNum);
      wLastSpace = curW;
      if (curW >= w)  {
	while (i+1 == ' ')
	  ++i;
	curH += fontH;
	wLastSpace = curW = 0;
      }
    } else  {
      curW += butEnv_charWidth(env, text+i, fontNum);
      if (text[i] <= '\2')
	++i;
      if (curW > w)  {
	curH += fontH;
	if (wLastSpace)  {
	  curW -= wLastSpace;
	  wLastSpace = 0;
	} else  {

	  curW = butEnv_charWidth(env, text+i, fontNum);
	}
      }
    }
  }
  return(curH);
}
