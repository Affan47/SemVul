Lsharp_dollar_reader()
{
	object x;
	enum type tx;

	check_arg(3);
	if (vs_base[2] != Cnil && !READsuppress)
		extra_argument('$');
	vs_popp;
	vs_popp;
	x = read_object(vs_base[0]);
	tx=type_of(x);
	vs_base[0] = alloc_object(t_random);
	init_gmp_rnd_state(&vs_base[0]->rnd.rnd_state);
	if (tx!=t_fixnum || fix(x)) {
	  if (tx==t_fixnum) {
	    if (vs_base[0]->rnd.rnd_state._mp_seed->_mp_size!=1)
	      FEerror("Cannot make a random-state with the value ~S.",1, x);
	    mpz_set_ui(vs_base[0]->rnd.rnd_state._mp_seed,fix(x));
	  } else {
	    if (x->big.big_mpz_t._mp_size!=vs_base[0]->rnd.rnd_state._mp_seed->_mp_size)
	      FEerror("Cannot make a random-state with the value ~S.",1, x);
	    memcpy(vs_base[0]->rnd.rnd_state._mp_seed->_mp_d,x->big.big_mpz_t._mp_d,
		   vs_base[0]->rnd.rnd_state._mp_seed->_mp_size*sizeof(*vs_base[0]->rnd.rnd_state._mp_seed->_mp_d));
	  }
	}

}
