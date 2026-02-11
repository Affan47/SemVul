gen_rand_pass (char *password_string, int minl, int maxl, unsigned int pass_mode)
{
  int i = 0;
  int j = 0;
  int length = 0;
  char *str_pointer;
  int random_weight[94];
  int max_weight = 0;
  int max_weight_element_number = 0;

  if (minl > APG_MAX_PASSWORD_LENGTH || maxl > APG_MAX_PASSWORD_LENGTH ||
      minl < 1 || maxl < 1 || minl > maxl)
      return (-1);
  for (i = 0; i <= 93; i++) random_weight[i] = 0;
  length = minl + randint(maxl-minl+1);
  str_pointer = password_string;

  for (i = 0; i < length; i++)
    {

      for (j = 0; j <= 93 ; j++)
         if ( ( (pass_mode & smbl[j].type) > 0) &&
	     !( (S_RS & smbl[j].type) > 0))
	    random_weight[j] = 1 + randint(20000);
      j = 0;

      for (j = 0; j <= 93; j++)
	if (random_weight[j] > max_weight)
	  {
	    max_weight = random_weight[j];
	    max_weight_element_number = j;
	  }

      *str_pointer = smbl[max_weight_element_number].ch;
      str_pointer++;
      max_weight = 0;
      max_weight_element_number = 0;
      for (j = 0; j <= 93; j++) random_weight[j] = 0;
    }
  *str_pointer = 0;
  return (length);
}
