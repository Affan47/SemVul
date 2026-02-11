substitute_aliases(World *world, const char *cmd)
{
  GSList *aliasptr;
  Alias  *alias;
  char   *result;
  int     i;

  if (world->disable_aliases) {
    return NULL;
  }

  aliasptr = world->aliases;
  i = 0;
  while (aliasptr) {
    alias = (Alias *) aliasptr->data;
    if (alias->enabled && (result = perl_substitute(world->perl_interpreter,
                                                    cmd,
                                                    alias->pattern_re,
                                                    alias->substitution,
                                                    alias->perl_eval,
                                                    FALSE))) {
      if (debug_matches) {
        fprintf(stderr,
                "**Alias %d '%s' matched for world %s\n"
                "  Command: %s\n"
                "  Pattern: %s\n"
                "  Substitution: %s\n"
                "  Eval as Perl: %d\n"
                "  Result: %s\n",
                i,
                alias->name ? alias->name : "",
                world->name,
                cmd,
                alias->pattern,
                alias->substitution,
                alias->perl_eval,
                result);
      }

      return result;
    }
    aliasptr = aliasptr->next;
    ++i;
  }

  return NULL;
}
