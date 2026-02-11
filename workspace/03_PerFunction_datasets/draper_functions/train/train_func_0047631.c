DLsub(u, v)
       doublelong *u;
       doublelong *v;
{

       u->high -= v->high;
       if (v->low > u->low)
               u->high--;
       u->low -= v->low;
}
