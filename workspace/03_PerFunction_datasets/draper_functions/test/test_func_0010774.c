dc_sp_sound(int script, int* yield, int* preturnint, int sprite, int sparg)
{
  RETURN_NEG_IF_BAD_SPRITE(sprite);
  *preturnint = change_sprite(sprite, sparg, &spr[sprite].sound);
  if (sparg > 0)
    SoundPlayEffect(spr[sprite].sound,22050, 0, sprite, 1);
}
