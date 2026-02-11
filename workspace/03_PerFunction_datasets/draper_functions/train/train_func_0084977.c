OccurrenceExists(struct Occurrence *list,char *locator,enum representations rep_type,char *context)

{ struct Occurrence *op;

for (op = list; op != NULL; op=op->next)
   {
   if (strcmp(locator,op->locator) == 0 && strcmp(op->occurrence_context,context) == 0)
      {
      return op;
      }
   }

return NULL;
}
