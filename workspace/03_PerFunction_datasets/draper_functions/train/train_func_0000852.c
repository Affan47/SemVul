iks_sasl_mechanisms (iks *x)
{
	int sasl_mech = 0;

	while (x) {
		if (!iks_strcmp(iks_cdata(iks_child(x)), "DIGEST-MD5"))
			sasl_mech |= IKS_STREAM_SASL_MD5;
		else if (!iks_strcmp(iks_cdata(iks_child(x)), "PLAIN"))
			sasl_mech |= IKS_STREAM_SASL_PLAIN;
		x = iks_next_tag(x);
	}
	return sasl_mech;
}
