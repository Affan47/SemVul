makehash(UINT4 a) {
   U_CHAR *c = (U_CHAR *) &a;
   U_CHAR  d[4] = {0, 0, 0, 0};
   int i;

   for (i=0;i<4;i++) {
      d[3] = rseq_m[c[0]  ] + rseq_m[c[1]+1] + rseq_m[c[2]+2] + rseq_m[c[3]+3];
      d[2] = rseq_m[c[1]  ] + rseq_m[c[2]+1] + rseq_m[c[3]+2];
      d[1] = rseq_m[c[2]  ] + rseq_m[c[3]+1];
      d[0] = rseq_m[c[3]  ];
      a = * (int *) &d[0];
   }

   return a;
}
