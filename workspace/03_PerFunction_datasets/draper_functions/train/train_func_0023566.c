recordWr(const Value *v, const int ready)
{
   int a = v->reg.data.id;

   if (v->reg.file == FILE_GPR) {
      int b = a + v->reg.size / 4;
      for (int r = a; r < b; ++r)
         score->rd.r[r] = ready;
   } else

   if (v->reg.file == FILE_PREDICATE) {
      score->rd.p[a] = ready + 4;
   } else {
      assert(v->reg.file == FILE_FLAGS);
      score->rd.c = ready + 4;
   }
}
