ec_deinit (void *opaque)
{
  mpi_ec_t ctx = opaque;
  int i;

  _gcry_mpi_barrett_free (ctx->t.p_barrett);


  mpi_free (ctx->p);
  mpi_free (ctx->a);
  mpi_free (ctx->b);
  _gcry_mpi_point_release (ctx->G);
  mpi_free (ctx->n);


  _gcry_mpi_point_release (ctx->Q);
  mpi_free (ctx->d);


  mpi_free (ctx->t.two_inv_p);

  for (i=0; i< DIM(ctx->t.scratch); i++)
    mpi_free (ctx->t.scratch[i]);


}
