GenerateRandom(RandomNumberGenerator &rng, const NameValuePairs &alg)
{
	Integer p, q, g;

	if (alg.GetValue("Modulus", p) && alg.GetValue("SubgroupGenerator", g))
	{
		q = alg.GetValueWithDefault("SubgroupOrder", ComputeGroupOrder(p)/2);
	}
	else
	{
		int modulusSize, subgroupOrderSize;

		if (!alg.GetIntValue("ModulusSize", modulusSize))
			modulusSize = alg.GetIntValueWithDefault("KeySize", 2048);

		if (!alg.GetIntValue("SubgroupOrderSize", subgroupOrderSize))
			subgroupOrderSize = GetDefaultSubgroupOrderSize(modulusSize);

		PrimeAndGenerator pg;
		pg.Generate(GetFieldType() == 1 ? 1 : -1, rng, modulusSize, subgroupOrderSize);
		p = pg.Prime();
		q = pg.SubPrime();
		g = pg.Generator();
	}

	Initialize(p, q, g);
}
