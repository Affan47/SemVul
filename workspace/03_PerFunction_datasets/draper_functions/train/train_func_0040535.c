init_reg_modes_once (void)
{
  int i;

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    {
      reg_raw_mode[i] = choose_hard_reg_mode (i, 1, false);


      if (reg_raw_mode[i] == VOIDmode)
	reg_raw_mode[i] = i == 0 ? word_mode : reg_raw_mode[i-1];
    }
}
