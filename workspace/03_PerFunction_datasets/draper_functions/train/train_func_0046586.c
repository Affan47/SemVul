should_log(struct gl_context *ctx,
           enum mesa_debug_source source,
           enum mesa_debug_type type,
           GLuint id,
           enum mesa_debug_severity severity)
{
   GLint gstack = ctx->Debug.GroupStackDepth;
   struct gl_debug_namespace *nspace =
         &ctx->Debug.Namespaces[gstack][source][type];
   uintptr_t state;

   if (!ctx->Debug.DebugOutput)
      return GL_FALSE;


   if (id)
      state = (uintptr_t)_mesa_HashLookup(nspace->IDs, id);
   else
      state = nspace->ZeroID;


   if (!(state & KNOWN_SEVERITY)) {
      struct gl_debug_severity *entry;

      if (state == NOT_FOUND) {
         if (ctx->Debug.Defaults[gstack][severity][source][type])
            state = ENABLED;
         else
            state = DISABLED;
      }

      entry = malloc(sizeof *entry);
      if (!entry)
         goto out;

      state |= KNOWN_SEVERITY;

      if (id)
         _mesa_HashInsert(nspace->IDs, id, (void*)state);
      else
         nspace->ZeroID = state;

      entry->ID = id;
      insert_at_tail(&nspace->Severity[severity], &entry->link);
   }

out:
   return !!(state & ENABLED_BIT);
}
