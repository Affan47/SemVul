dump
(  tn* node
,  i32  times
,  const char* msg
)
   {  tn* prev = NULL
   ;  printf("______ %s\n", msg ? msg : "dumping dumping dumping")
   ;  printf
("%8s"     "%10s"   "%10s"    "%10s"  "%12s" "%10s" "%6s\n"
,"toktype","optype","opclass","token","fval","ival","flags"
)
   ;  while (node)
      {  printf
("%8d"     "%10d"   "%10d"    "%10s"  "%12.4f""%10ld""%6d\n"
         ,  node->toktype
         ,  node->opid
         ,  node->optype
         ,  node->token ? node->token->str : "<>"
         ,  node->fval
         ,  (long) node->ival
         ,  node->flags
         )
      ;  prev = node
      ;  node = node->next
      ;  if (node && (node->prev->next != node || node->prev != prev))
         fprintf
         (  stderr
         ,  "_____ [telraam] PANICK incorrect linking"
            " <%p> n<%p> np<%p> npn<%p>\n"
         ,  (void*) prev
         ,  (void*) node
         ,  (void*) node->prev
         ,  (void*) node->prev->next
         )
      ;  if (!--times)
         break
   ;  }
   }
