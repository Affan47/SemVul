Use_Plat (edict_t * ent, edict_t * other, edict_t * activator)
{
  if (ent->think)
    return;
  plat_go_down (ent);
}
