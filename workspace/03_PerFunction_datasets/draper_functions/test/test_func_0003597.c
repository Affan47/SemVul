apply(const plan *ego_, R *ri, R *ii, R *ro, R *io)
{
     const P *ego = (const P *) ego_;
     INT i;
     INT n = ego->n, is = ego->is, os = ego->os;
     const R *W = ego->td->W;
     E *buf;
     size_t bufsz = n * 2 * sizeof(E);

     BUF_ALLOC(E *, buf, bufsz);
     hartley(n, ri, ii, is, buf, ro, io);

     for (i = 1; i + i < n; ++i) {
	  cdot(n, buf, W,
	       ro + i * os, io + i * os,
	       ro + (n - i) * os, io + (n - i) * os);
	  W += n - 1;
     }

     BUF_FREE(buf, bufsz);
}
