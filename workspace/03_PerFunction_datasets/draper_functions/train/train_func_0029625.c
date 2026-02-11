dc_sp_hard(int script, int* yield, int* preturnint, int sprite, int sparg)
{
  RETURN_NEG_IF_BAD_SPRITE(sprite);
  *preturnint = change_sprite(sprite, sparg, &spr[sprite].hard);
  if (spr[sprite].sp_index != 0 && sparg != -1)
    pam.sprite[spr[sprite].sp_index].hard = *preturnint;
}
