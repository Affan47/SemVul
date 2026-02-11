newpass_bag(PKCS12_SAFEBAG *bag, char *oldpass, char *newpass)
{
	PKCS8_PRIV_KEY_INFO *p8;
	X509_SIG *p8new;
	int p8_nid, p8_saltlen, p8_iter;

	if(M_PKCS12_bag_type(bag) != NID_pkcs8ShroudedKeyBag) return 1;

	if (!(p8 = PKCS8_decrypt(bag->value.shkeybag, oldpass, -1))) return 0;
	if (!alg_get(bag->value.shkeybag->algor, &p8_nid, &p8_iter,
							&p8_saltlen))
		return 0;
	if(!(p8new = PKCS8_encrypt(p8_nid, NULL, newpass, -1, NULL, p8_saltlen,
						     p8_iter, p8))) return 0;
	X509_SIG_free(bag->value.shkeybag);
	bag->value.shkeybag = p8new;
	return 1;
}
