callbackKeyboard (Component *comp, int key)
{
  int i;
  for (i = 5; i < 16; i ++)
    if (comp == controlsmenu [0]->components [i])
    {
      int z = 5;
      if (i == z ++) key_firecannon = key;
      else if (i == z ++) key_firemissile = key;
      else if (i == z ++) key_dropflare = key;
      else if (i == z ++) key_dropchaff = key;
      else if (i == z ++) key_selectmissile = key;
      else if (i == z ++) key_targetnearest = key;
      else if (i == z ++) key_targetlocking = key;
      else if (i == z ++) key_targetnext = key;
      else if (i == z ++) key_targetprevious = key;
      else if (i == z ++) key_thrustup = key;
      else if (i == z ++) key_thrustdown = key;
    }
}
