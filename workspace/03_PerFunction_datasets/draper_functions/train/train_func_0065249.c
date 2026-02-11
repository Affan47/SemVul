stack_usage ARGS1((ex ),
struct expnode *ex)
{ int usage = 0;
  struct treenode *node ;
#ifdef _DEBUG
  int didwarn = 0;
#endif

  ex->stack_max = 0;
  for ( node = ex->start+1 ; node->type != FINISHED ; node++ )
  { usage += node->stack_delta;
    if ( usage > ex->stack_max ) ex->stack_max = usage;
#ifdef _DEBUG
    if ( (usage < 0) && (!didwarn) )
    { sprintf(errmsg,"Internal error: stack usage negative, node type %d.\n",
        node->type);
      sprintf(errmsg+strlen(errmsg),"(source file %s, line %d)\n",
         file_names[node->file_no],node->line_no);
      kb_error(2670,errmsg,WARNING);
      didwarn = 1;
    }
    node->stack_spot = usage;
#endif
  }
}
