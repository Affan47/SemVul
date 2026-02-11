SHA1_Init_With_IV( SHA1_ctx* ctx,
			const byte user_IV[ SHA1_DIGEST_BYTES ] )
{
    SHA1_zero_bitcount( ctx );
    memcpy( ctx->H, user_IV, SHA1_DIGEST_BYTES );
    make_local_endian32( ctx->H, SHA1_DIGEST_WORDS );
}
