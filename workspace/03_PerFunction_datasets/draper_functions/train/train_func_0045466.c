is_valid_BN(BIGNUM *bn) {

    printf("BN { d=%p, top=%i, dmax=%i, neg=%i, flags=%i }\n",
		bn->d, bn->top, bn->dmax, bn->neg, bn->flags);
	  if ( bn->dmax < 0 || bn->top < 0 || bn->dmax < bn->top )
				return -1;

    if ( !(bn->neg == 1 || bn->neg == 0 ) ) {
        return -1;
    }
    return 0;
}
