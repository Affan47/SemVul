rrtype_getinfo(u_int16 type) {
   int t;
   for (t = 0; t < n_rr_types; t++)
     if (rr_types[t].type == type) return (rr_type *)&rr_types[t];

   return NULL;
}
