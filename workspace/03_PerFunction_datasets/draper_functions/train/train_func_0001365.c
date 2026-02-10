dc_sp_custom(int script, int* yield, int* preturnint, char* key, int sprite, int val)
{
  RETURN_NEG_IF_BAD_SPRITE(sprite);
  if (spr[sprite].active == 0)
    {
      *preturnint = -1;
    }
  else
    {

      if (val != -1)
	dinkc_sp_custom_set(spr[sprite].custom, key, val);
      *preturnint = dinkc_sp_custom_get(spr[sprite].custom, key);
    }
}
