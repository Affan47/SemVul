opt_deadstores(b)
   register struct block *b;
{
   register struct slist *s;
   register int atom;
   struct stmt *last[N_ATOMS];

   memset((char *)last, 0, sizeof last);

   for (s = b->stmts; s != 0; s = s->next)
      deadstmt(&s->s, last);
   deadstmt(&b->s, last);

   for (atom = 0; atom < N_ATOMS; ++atom)
      if (last[atom] && !ATOMELEM(b->out_use, atom)) {
         last[atom]->code = NOP;
         done = 0;
      }
}
