primeN_trialDivision(unsigned n){
	struct w1_vect* primes = NULL;
	struct w1_iter* itr = NULL;
	unsigned count = 1;
	unsigned last = 3;

	if(n <= 1){
		return 2;
	}

	primes = w1vect_init(AUTO,UNSIGNED);
	if(!primes){
		goto fail;
	}
	itr = w1vect_initIter(primes);
	if(!itr){
		goto fail;
	}

	while(count < n){

		w1vect_appendUnsigned(primes,last);

		do{
			last += 2;
		}while(!trialDivideVect(primes,itr,last));

		count++;
	}

	w1vect_free(primes);
	w1vect_freeIter(itr);

	return last;

	fail:
	w1vect_free(primes);
	w1vect_freeIter(itr);
	return 0;
}
