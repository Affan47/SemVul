bloops_track_str(bloopsatrack *track)
{
  int bufsize = sizeof(char) * (track->nlen * 6 + 1024);
  char *str = (char *)malloc(bufsize), *ptr = str;
  int i, adv = 0;

  for (i = 0; i < track->nlen; i++)
  {
    if (ptr - str + adv + sizeof(char) * 256 > bufsize) {
      char *new_str;
      bufsize += sizeof(char) * 1024;
      new_str = realloc(str, bufsize);
      if (new_str == NULL) {
        free(str);
        return NULL;
      }
    }

    if (ptr > str)
      strcat(ptr++, " ");

    if (track->notes[i].duration != 4)
    {
      adv = sprintf(ptr, "%d:", (int)track->notes[i].duration);
      ptr += adv;
    }

    if (track->notes[i].tone)
    {
      char tone[3] = "\0\0\0";
      tone[0] = track->notes[i].tone;
      switch (tone[0]) {
        case 'a': tone[0] = 'A'; tone[1] = 'b'; break;
        case 'b': tone[0] = 'B'; tone[1] = 'b'; break;
        case 'd': tone[0] = 'C'; tone[1] = '#'; break;
        case 'e': tone[0] = 'E'; tone[1] = 'b'; break;
        case 'g': tone[0] = 'F'; tone[1] = '#'; break;
      }
      adv = sprintf(ptr, "%s", tone);
      ptr += adv;

      adv = sprintf(ptr, "%d", (int)track->notes[i].octave);
      ptr += adv;
      bloopsafx *fx = (bloopsafx *)track->notes[i].FX;
      while (fx) {
        if (fx->mod == 0)
          adv = sprintf(ptr, "[%s %0.3f]", bloops_fxcmd_name(fx->cmd), fx->val);
        else
          adv = sprintf(ptr, "[%s %c %0.3f]", bloops_fxcmd_name(fx->cmd), fx->mod, fx->val);
        ptr += adv;
        fx = (bloopsafx *)fx->next;
      }
    }
  }

  return str;
}
