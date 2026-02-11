Think_SpawnDoorTrigger (edict_t * ent)
{
  edict_t *other;
  vec3_t mins, maxs;

  if (ent->flags & FL_TEAMSLAVE)
    return;

  VectorCopy (ent->absmin, mins);
  VectorCopy (ent->absmax, maxs);

  for (other = ent->teamchain; other; other = other->teamchain)
    {
      AddPointToBounds (other->absmin, mins, maxs);
      AddPointToBounds (other->absmax, mins, maxs);
    }


  mins[0] -= 60;
  mins[1] -= 60;
  maxs[0] += 60;
  maxs[1] += 60;

  other = G_Spawn ();
  VectorCopy (mins, other->mins);
  VectorCopy (maxs, other->maxs);
  other->owner = ent;
  other->solid = SOLID_TRIGGER;
  other->movetype = MOVETYPE_NONE;
  other->touch = Touch_DoorTrigger;
  gi.linkentity (other);

  if (ent->spawnflags & DOOR_START_OPEN)
    door_use_areaportals (ent, true);

  Think_CalcMoveSpeed (ent);
}
