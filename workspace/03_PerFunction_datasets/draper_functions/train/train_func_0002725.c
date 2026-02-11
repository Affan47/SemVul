Improve(struct state *st)
{
  if (st->smart)
	 return;
  if (st->level > 20)
	 return;
  st->aim -= 4;
  if (st->level <= 2) st->aim -= 8;
  if (st->level <= 5) st->aim -= 6;
  if (st->gamez < 3)
	 st->aim -= 10;
  st->carefulpersen += 6;
  st->choosypersen += 4;
  if (st->level <= 5) st->choosypersen += 3;
  st->econpersen += 4;
  st->lrate -= 2;
  if (st->startlrate < kMinRate) {
	 if (st->lrate < st->startlrate)
		st->lrate = st->startlrate;
  }
  else {
	 if (st->lrate < kMinRate)
		st->lrate = kMinRate;
  }
  if (st->level <= 5) st->econpersen += 3;
  if (st->aim < 1) st->aim = 1;
  if (st->choosypersen > 100) st->choosypersen = 100;
  if (st->carefulpersen > 100) st->carefulpersen = 100;
  if (st->econpersen > 100) st->econpersen = 100;
}
