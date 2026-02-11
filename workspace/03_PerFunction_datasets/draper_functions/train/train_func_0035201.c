attack_init(int type, int num, char *ebuf)
{
  void *attack = NULL;

  if (!attack_string(type, num)) {
    strcpy(ebuf, "attack unimplemented");
    return NULL;
  }
  else if (type == ATTACK_BASE)
    attack = attack_baseline;
  else if (type == ATTACK_FRAG)
    attack = attack_frag;
  else if (type == ATTACK_TCP)
    attack = attack_tcp;
  else if (type == ATTACK_TCBC)
    attack = attack_tcbc;
  else if (type == ATTACK_TCBT)
    attack = attack_tcbt;
  else if (type == ATTACK_INSERT)
    attack = attack_insert;
  else if (type == ATTACK_MISC)
    attack = attack_misc;

  attack_type = type;
  attack_num = num;

  return attack;
}
