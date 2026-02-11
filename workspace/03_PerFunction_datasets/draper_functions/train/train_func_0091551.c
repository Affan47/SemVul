hack_attempt(player *p, int Security)
{
 if (Security == -1)
  Security = security;

 p->practice(sk_computer, 5 + Security * 2);
 int player_roll = p->sklevel[sk_computer];
 if (p->int_cur < 8 && one_in(2))
  player_roll -= rng(0, 8 - p->int_cur);
 else if (p->int_cur > 8 && one_in(3))
  player_roll += rng(0, p->int_cur - 8);

 return (dice(player_roll, 6) >= dice(Security, 6));
}
