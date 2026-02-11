iter_copy(const ITER *ip1, ITER *ip2)
#endif
{
   VEC *x, *b;

   if (ip1 == (ITER *)NULL)
     error(E_NULL,"iter_copy");

   if (ip2 == (ITER *)NULL) {
      if ((ip2 = NEW(ITER)) == (ITER *) NULL)
	error(E_MEM,"iter_copy2");
      else if (mem_info_is_on()) {
	 mem_bytes(TYPE_ITER,0,sizeof(ITER));
	 mem_numvar(TYPE_ITER,1);
      }
   }

   x = ip2->x;
   b = ip2->b;

   MEM_COPY(ip1,ip2,sizeof(ITER));
   if (ip1->x)
     ip2->x = v_copy(ip1->x,x);
   if (ip1->b)
     ip2->b = v_copy(ip1->b,b);

   ip2->shared_x = ip2->shared_b = FALSE;

   return ip2;
}
