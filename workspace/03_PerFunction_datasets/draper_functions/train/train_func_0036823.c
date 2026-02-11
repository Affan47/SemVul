calculate_missed_by(player &p, int trange)
{
 it_gun* firing = dynamic_cast<it_gun*>(p.weapon.type);

  double deviation = 0.;

  if (p.sklevel[firing->skill_used] < 4)
   deviation += rng(0, 6 * (4 - p.sklevel[firing->skill_used]));
  else if (p.sklevel[firing->skill_used] > 4)
   deviation -= rng(0, 5 * (p.sklevel[firing->skill_used] - 4));

  if (p.sklevel[sk_gun] < 3)
   deviation += rng(0, 3 * (3 - p.sklevel[sk_gun]));
  else
   deviation -= rng(0, 2 * (p.sklevel[sk_gun] - 3));

  deviation += p.ranged_dex_mod();
  deviation += p.ranged_per_mod();

  deviation += rng(0, 2 * p.encumb(bp_arms)) + rng(0, 4 * p.encumb(bp_eyes));

  deviation += rng(0, p.weapon.curammo->accuracy);
  deviation += rng(0, p.weapon.accuracy());
  int adj_recoil = p.recoil + p.driving_recoil;
  deviation += rng(int(adj_recoil / 4), adj_recoil);


  return (.00325 * deviation * trange);
}
