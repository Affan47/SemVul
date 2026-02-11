CL_PMSurfaceTrace (vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, int contentmask)
{
   trace_t   t;

   if (!mins)
      mins = vec3_origin;
   if (!maxs)
      maxs = vec3_origin;


   t = CM_BoxTrace (start, end, mins, maxs, 0, contentmask);
   if (t.fraction < 1.0)
      t.ent = (struct edict_s *)1;


   CL_ClipMoveToEntities (start, mins, maxs, end, &t);

   return t;
}
