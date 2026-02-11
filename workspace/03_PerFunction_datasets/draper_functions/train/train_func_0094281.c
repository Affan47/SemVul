IsSABME(u_char *data, struct layer2 *l2)
{
	u_char d = data[0] & ~0x10;

	return test_bit(FLG_MOD128, &l2->flag) ? d == SABME : d == SABM;
}
