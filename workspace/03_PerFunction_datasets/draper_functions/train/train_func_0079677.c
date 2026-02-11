seqiv_free(struct crypto_instance *inst)
{
	if ((inst->alg.cra_flags ^ CRYPTO_ALG_TYPE_AEAD) & CRYPTO_ALG_TYPE_MASK)
		skcipher_geniv_free(inst);
	else
		aead_geniv_free(aead_instance(inst));
}
