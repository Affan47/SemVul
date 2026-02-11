trigger_elevator_use (edict_t * self, edict_t * other, edict_t * activator)
{
  edict_t *target;

  if (self->movetarget->nextthink)
    {

      return;
    }

  if (!other->pathtarget)
    {
      gi.dprintf ("elevator used with no pathtarget\n");
      return;
    }

  target = G_PickTarget (other->pathtarget);
  if (!target)
    {
      gi.dprintf ("elevator used with bad pathtarget: %s\n",
		  other->pathtarget);
      return;
    }

  self->movetarget->target_ent = target;
  train_resume (self->movetarget);
}
