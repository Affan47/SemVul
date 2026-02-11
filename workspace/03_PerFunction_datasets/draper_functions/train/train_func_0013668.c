apply_buf(const plan *ego_, R *IO)
{
     const P *ego = (const P *) ego_;
     plan_rdft *cld0 = (plan_rdft *) ego->cld0;
     plan_rdft *cldm = (plan_rdft *) ego->cldm;
     INT i, j, m = ego->m, v = ego->v, r = ego->r;
     INT mb = ego->mb, me = ego->me, ms = ego->ms;
     INT batchsz = compute_batchsize(r);
     R *buf;
     size_t bufsz = r * batchsz * 2 * sizeof(R);

     BUF_ALLOC(R *, buf, bufsz);

     for (i = 0; i < v; ++i, IO += ego->vs) {
	  R *IOp = IO;
	  R *IOm = IO + m * ms;

	  cld0->apply((plan *) cld0, IO, IO);

	  for (j = mb; j + batchsz < me; j += batchsz)
	       dobatch(ego, IOp, IOm, j, j + batchsz, buf);

	  dobatch(ego, IOp, IOm, j, me, buf);

	  cldm->apply((plan *) cldm, IO + ms * (m/2), IO + ms * (m/2));
     }

     BUF_FREE(buf, bufsz);
}
