countPrimeFactors(
		struct trialPrimeGen* gen, unsigned n,
		struct w1_vect* mem
	){

	struct primeCount counts = {0,mem};
	unsigned root = gteSquareRoot(n);
	unsigned prime;
	unsigned pInd = 0;

	w1vect_reset(mem);

	if(!gen->v->len){
		prime = trailDivideGenNext(gen);
	}
	else{
		prime = w1vect_getIndUnsigned(gen->v,pInd);
	}

	do{
		pInd += 1;

		if(!(n%prime)){


			unsigned power = prime*prime;
			unsigned powerCount = divCount(n,power,prime);
			counts.primes += 1;

			if(powerCount){
				w1vect_appendUnsigned(
						counts.powers,powerCount
					);
			}
		}

		if(pInd >= gen->v->len){
			prime = trailDivideGenNext(gen);
		}
		else{
			prime = w1vect_getIndUnsigned(gen->v,pInd);
		}

	}while(prime <= root);

	if(!counts.primes){


		counts.primes += 1;
	}

	return counts;
}
