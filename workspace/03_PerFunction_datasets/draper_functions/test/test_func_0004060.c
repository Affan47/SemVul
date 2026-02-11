extract_rsa_key(RSA *rsa, proc_t *p) {

    int error = 0;

		if ( verbose > 1 ) {
				printf("RSA { pad=%i, ver=%li, ref=%i, flags=%i, engine=%p\n"
								"      n=%p, e=%p, d=%p, p=%p, q=%p\n"
								"      dmp1=%p, dmq1=%p, iqmp=%p, bn_data=%p\n"
								"      blinding=%p, mont_bn=%p/%p/%p }\n",
								rsa->pad, rsa->version, rsa->references, rsa->flags, rsa->engine,
								rsa->n, rsa->e, rsa->d, rsa->p, rsa->q, rsa->dmp1, rsa->dmq1,
								rsa->iqmp, rsa->bignum_data, rsa->blinding,
								rsa->_method_mod_n, rsa->_method_mod_p, rsa->_method_mod_q);
		}

    rsa->n =    BN_extract_from_mem(rsa->n, p, &error);
    if ( error ) return -1;
    rsa->e =    BN_extract_from_mem(rsa->e, p, &error);
    if ( error ) { goto free_n; }
    rsa->d =    BN_extract_from_mem(rsa->d, p, &error);
    if ( error ) { goto free_e; }
    rsa->p =    BN_extract_from_mem(rsa->p, p, &error);
    if ( error ) { goto free_d; }
    rsa->q =    BN_extract_from_mem(rsa->q, p, &error);
    if ( error ) { goto free_p; }
    rsa->dmp1 = BN_extract_from_mem(rsa->dmp1, p, &error);
    if ( error ) { goto free_q; }
    rsa->dmq1 = BN_extract_from_mem(rsa->dmq1, p, &error);
    if ( error ) { goto free_dmp1; }
    rsa->iqmp = BN_extract_from_mem(rsa->iqmp, p, &error);
    if ( error ) { goto free_dmq1; }

	rsa->meth = NULL;
	rsa->_method_mod_n = NULL;
	rsa->_method_mod_p = NULL;
	rsa->_method_mod_q = NULL;
	rsa->bignum_data = NULL;
	rsa->blinding = NULL;


	 switch ( RSA_check_key( rsa )) {
		 case 1 :
			 return 0;
		 case 0 :
			 if (verbose > 1)
				 fprintf(stderr, "warn: invalid RSA key found.\n");
			 break;
		 case -1 :
			 if (verbose > 1)
				 fprintf(stderr, "warn: unable to check key.\n");
			 break;
	 }

    free(rsa->iqmp);
free_dmq1 :
    free(rsa->dmq1);
free_dmp1 :
    free(rsa->dmp1);
free_q :
    free(rsa->q);
free_p :
    free(rsa->p);
free_d :
    free(rsa->d);
free_e :
    free(rsa->e);
free_n :
    free(rsa->n);

    return -1 ;
}
