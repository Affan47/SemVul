kullback_leibler_div(const nlookup_t *nl, size_t nodes, int bmin,
	size_t prefix[KDA_C + 1], struct kl_item items[KDA_C + 1])
{
	double M[KDA_C + 1];
	double dkl;
	size_t i;

	g_assert(nodes <= KDA_K);
	g_assert(size_is_positive(nodes));

	for (i = 0; i < UNSIGNED(KDA_C + 1); i++) {
		g_assert(prefix[i] <= nodes);
		M[i] = (double) prefix[i] / nodes;
	}

	dkl = 0.0;

	for (i = 0; i < G_N_ELEMENTS(M); i++) {
		double ct;

		items[i].prefix = i + bmin;

		if (0 == prefix[i]) {
			items[i].contrib = 0.0;
			continue;
		}


		ct = M[i] * (log2_frequency[nodes - 1][prefix[i] - 1] + (i + 1.0));
		dkl += ct;
		items[i].contrib = ct;

		if (GNET_PROPERTY(dht_lookup_debug) > 2) {
			g_debug("DHT LOOKUP[%s] %u-bit prefix: "
				"freq = %g (%u/%u node%s, log2=%g), theoric = %g => "
				"K-L contribution: %g",
				nid_to_string(&nl->lid), (unsigned) (i + bmin),
				M[i], (unsigned) prefix[i], (unsigned) nodes,
				1 == prefix[i] ? "" : "s",
				log2_frequency[nodes - 1][prefix[i] - 1],
				1.0 / pow(2.0, i + 1.0), ct);
		}
	}

	return dkl;
}
