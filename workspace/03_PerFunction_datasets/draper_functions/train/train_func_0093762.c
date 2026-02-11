merge_key(const BF_round_key_set expkey, BF_key_schedule *ks)
{
	int i;
	for(i = BF_N + 2; i--; ) {
		ks->P[i] ^= expkey[i];
	}
}
