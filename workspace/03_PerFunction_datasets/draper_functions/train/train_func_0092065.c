mod_exp_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    BIGNUM *bn_base=NULL, *bn_exponent=NULL, *bn_modulo, *bn_result;
    BN_CTX *bn_ctx;
    unsigned char* ptr;
    unsigned dlen;
    unsigned bin_hdr;
    unsigned extra_byte;
    ERL_NIF_TERM ret;

    if (!get_bn_from_bin(env, argv[0], &bn_base)
	|| !get_bn_from_bin(env, argv[1], &bn_exponent)
	|| !get_bn_from_bin(env, argv[2], &bn_modulo)
	|| !enif_get_uint(env,argv[3],&bin_hdr) || (bin_hdr & ~4)) {

	if (bn_base) BN_free(bn_base);
	if (bn_exponent) BN_free(bn_exponent);
	return enif_make_badarg(env);
    }
    bn_result = BN_new();
    bn_ctx = BN_CTX_new();
    BN_mod_exp(bn_result, bn_base, bn_exponent, bn_modulo, bn_ctx);
    dlen = BN_num_bytes(bn_result);
    extra_byte = bin_hdr && BN_is_bit_set(bn_result, dlen*8-1);
    ptr = enif_make_new_binary(env, bin_hdr+extra_byte+dlen, &ret);
    if (bin_hdr) {
	put_int32(ptr, extra_byte+dlen);
	ptr[4] = 0;
	ptr += bin_hdr + extra_byte;
    }
    BN_bn2bin(bn_result, ptr);
    BN_free(bn_result);
    BN_CTX_free(bn_ctx);
    BN_free(bn_modulo);
    BN_free(bn_exponent);
    BN_free(bn_base);
    return ret;
}
