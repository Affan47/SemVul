visit(ir_swizzle *ir)
{
   const unsigned swiz[4] = {
      ir->mask.x,
      ir->mask.y,
      ir->mask.z,
      ir->mask.w,
   };

   printf("(swiz ");
   for (unsigned i = 0; i < ir->mask.num_components; i++) {
      printf("%c", "xyzw"[swiz[i]]);
   }
   printf(" ");
   ir->val->accept(this);
   printf(")");
}
