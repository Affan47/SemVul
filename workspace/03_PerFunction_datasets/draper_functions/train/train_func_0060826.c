_cmsSearchTag(_cmsICCPROFILE* Icc, cmsTagSignature sig, cmsBool lFollowLinks)
{
	int n;
	cmsTagSignature LinkedSig;

	do {


		n = SearchOneTag(Icc, sig);
		if (n < 0)
			return -1;

		if (!lFollowLinks)
			return n;


		LinkedSig = Icc ->TagLinked[n];


		if (LinkedSig != (cmsTagSignature) 0) {
			sig = LinkedSig;
		}

	} while (LinkedSig != (cmsTagSignature) 0);

	return n;
}
