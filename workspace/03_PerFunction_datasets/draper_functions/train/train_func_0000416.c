one_of_both_attackable(int pos, int what)
{
  UNUSED(pos);
  return (all_data[what].reason1 == DEFEND_STRING
      	  && all_data[what].reason2 == DEFEND_STRING
   	  && (worm[all_data[what].what1].attack_codes[0] != 0
              || worm[all_data[what].what2].attack_codes[0] != 0));
}
