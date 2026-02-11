_gcry_mpih_mul_karatsuba_case( mpi_ptr_t prodp,
                                  mpi_ptr_t up, mpi_size_t usize,
                                  mpi_ptr_t vp, mpi_size_t vsize,
                                  struct karatsuba_ctx *ctx )
{
    mpi_limb_t cy;

    if( !ctx->tspace || ctx->tspace_size < vsize ) {
	if( ctx->tspace )
	    _gcry_mpi_free_limb_space( ctx->tspace, ctx->tspace_nlimbs );
        ctx->tspace_nlimbs = 2 * vsize;
	ctx->tspace = mpi_alloc_limb_space (2 * vsize,
				            (_gcry_is_secure (up)
                                             || _gcry_is_secure (vp)));
	ctx->tspace_size = vsize;
    }

    MPN_MUL_N_RECURSE( prodp, up, vp, vsize, ctx->tspace );

    prodp += vsize;
    up += vsize;
    usize -= vsize;
    if( usize >= vsize ) {
	if( !ctx->tp || ctx->tp_size < vsize ) {
	    if( ctx->tp )
		_gcry_mpi_free_limb_space( ctx->tp, ctx->tp_nlimbs );
            ctx->tp_nlimbs = 2 * vsize;
	    ctx->tp = mpi_alloc_limb_space (2 * vsize,
                                            (_gcry_is_secure (up)
                                             || _gcry_is_secure (vp)));
	    ctx->tp_size = vsize;
	}

	do {
	    MPN_MUL_N_RECURSE( ctx->tp, up, vp, vsize, ctx->tspace );
	    cy = _gcry_mpih_add_n( prodp, prodp, ctx->tp, vsize );
	    _gcry_mpih_add_1( prodp + vsize, ctx->tp + vsize, vsize, cy );
	    prodp += vsize;
	    up += vsize;
	    usize -= vsize;
	} while( usize >= vsize );
    }

    if( usize ) {
	if( usize < KARATSUBA_THRESHOLD ) {
	    _gcry_mpih_mul( ctx->tspace, vp, vsize, up, usize );
	}
	else {
	    if( !ctx->next ) {
		ctx->next = xcalloc( 1, sizeof *ctx );
	    }
	    _gcry_mpih_mul_karatsuba_case( ctx->tspace,
					vp, vsize,
					up, usize,
					ctx->next );
	}

	cy = _gcry_mpih_add_n( prodp, prodp, ctx->tspace, vsize);
	_gcry_mpih_add_1( prodp + vsize, ctx->tspace + vsize, usize, cy );
    }
}
