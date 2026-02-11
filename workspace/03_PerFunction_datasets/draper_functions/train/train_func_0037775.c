aes_generic_decrypt_xts(aes_block *output, aes_key *k1, aes_key *k2, aes_block *dataunit,
                             uint32_t spoint, aes_block *input, uint32_t nb_blocks)
{
	aes_block block, tweak;


	block128_copy(&tweak, dataunit);
	aes_encrypt_block(&tweak, k2, &tweak);


	while (spoint-- > 0)
		gf_mulx(&tweak);

	for ( ; nb_blocks-- > 0; input++, output++, gf_mulx(&tweak)) {
		block128_vxor(&block, input, &tweak);
		aes_decrypt_block(&block, k1, &block);
		block128_vxor(output, &block, &tweak);
	}
}
