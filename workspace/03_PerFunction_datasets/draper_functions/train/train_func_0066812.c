_mesa_ast_type_qualifier_print(const struct ast_type_qualifier *q)
{
   if (q->flags.q.constant)
      printf("const ");

   if (q->flags.q.invariant)
      printf("invariant ");

   if (q->flags.q.attribute)
      printf("attribute ");

   if (q->flags.q.varying)
      printf("varying ");

   if (q->flags.q.in && q->flags.q.out)
      printf("inout ");
   else {
      if (q->flags.q.in)
	 printf("in ");

      if (q->flags.q.out)
	 printf("out ");
   }

   if (q->flags.q.centroid)
      printf("centroid ");
   if (q->flags.q.sample)
      printf("sample ");
   if (q->flags.q.uniform)
      printf("uniform ");
   if (q->flags.q.smooth)
      printf("smooth ");
   if (q->flags.q.flat)
      printf("flat ");
   if (q->flags.q.noperspective)
      printf("noperspective ");
}
