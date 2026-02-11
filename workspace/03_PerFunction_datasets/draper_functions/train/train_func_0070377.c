hidden_covering(NPP *npp, struct elem *ptr, double *_b)
{


      struct elem *e;
      int neg;
      double b = *_b, eps;
      xassert(npp == npp);

      for (e = ptr; e != NULL; e = e->next)
      {  xassert(e->aj != 0.0);
         xassert(e->xj->is_int);
         xassert(e->xj->lb == 0.0 && e->xj->ub == 1.0);
      }


      neg = 0;
      for (e = ptr; e != NULL; e = e->next)
      {  if (e->aj == +1.0)
            ;
         else if (e->aj == -1.0)
            neg++;
         else
            break;
      }
      if (e == NULL)
      {
         if (b == (double)(1 - neg))
         {
            return 1;
         }
      }


      for (e = ptr; e != NULL; e = e->next)
         if (e->aj < 0) b -= e->aj;


      if (b < 1e-3) return 0;


      eps = 1e-9 + 1e-12 * fabs(b);
      for (e = ptr; e != NULL; e = e->next)
         if (fabs(e->aj) < b - eps) return 0;


      b = 1.0;
      for (e = ptr; e != NULL; e = e->next)
      {  if (e->aj > 0.0)
            e->aj = +1.0;
         else
            e->aj = -1.0, b -= 1.0;
      }
      *_b = b;
      return 2;
}
