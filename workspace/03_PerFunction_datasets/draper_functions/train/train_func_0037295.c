init()
{
  if (!force->kspace)
    error->all(FLERR,"Cannot use fix tune/kspace without a kspace style");
  if (!force->pair)
    error->all(FLERR,"Cannot use fix tune/kspace without a pair style");

  double old_acc = force->kspace->accuracy/force->kspace->two_charge_force;
  char old_acc_str[12];
  sprintf(old_acc_str,"%g",old_acc);
  strcpy(new_acc_str,old_acc_str);

  int itmp;
  double *p_cutoff = (double *) force->pair->extract("cut_coul",itmp);
  pair_cut_coul = *p_cutoff;
}
