SV_PushEntity (edict_t * ent, vec3_t push)
{
  trace_t trace;
  vec3_t start;
  vec3_t end;
  int mask;

  VectorCopy (ent->s.origin, start);
  VectorAdd (start, push, end);

retry:
  if (ent->clipmask)
    mask = ent->clipmask;
  else
    mask = MASK_SOLID;

  PRETRACE ();
  trace = gi.trace (start, ent->mins, ent->maxs, end, ent, mask);
  POSTTRACE ();

  VectorCopy (trace.endpos, ent->s.origin);
  if(ent->inuse)
	gi.linkentity (ent);

  if (trace.fraction != 1.0)
    {
      SV_Impact (ent, &trace);


      if (!trace.ent->inuse && ent->inuse)
	{

	  VectorCopy (start, ent->s.origin);
	  gi.linkentity (ent);
	  goto retry;
	}
    }

  if (ent->inuse)
    G_TouchTriggers (ent);

  return trace;
}
