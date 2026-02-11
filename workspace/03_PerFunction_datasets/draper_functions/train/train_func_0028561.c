isprime_Tabule(const int n)  const
	{
		int plus = LOGMAX >> 1;
		int here = plus;
		int a;


		for(int loop = LOGMAX;loop; (loop >>= 1) ) {
			if ( (a = (TP[here] - n)) == 0) return 1;
			if (a > 0)
				here -= (++plus >>= 1);
			else
				here += (++plus >>= 1);

		}
		return 0;
	}
