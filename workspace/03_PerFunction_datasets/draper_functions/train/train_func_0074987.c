iter_spmgcr(SPMAT *A, SPMAT *B, VEC *b, double tol,
		     VEC *x, int k, int limit, int *steps)
#endif
{
   ITER *ip;

   ip = iter_get(0,0);
   ip->Ax = (Fun_Ax) sp_mv_mlt;
   ip->A_par = (void *) A;
   if (B) {
      ip->Bx = (Fun_Ax) sp_mv_mlt;
      ip->B_par = (void *) B;
   }
   else {
      ip->Bx = (Fun_Ax) NULL;
      ip->B_par = NULL;
   }

   ip->k = k;
   ip->limit = limit;
   ip->info = (Fun_info) NULL;
   ip->b = b;
   ip->eps = tol;
   ip->x = x;
   iter_mgcr(ip);
   x = ip->x;
   if (steps) *steps = ip->steps;
   ip->shared_x = ip->shared_b = TRUE;
   iter_free(ip);
   return x;
}
