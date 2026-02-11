get_prime_factors (GMT_LONG n, GMT_LONG *f)
{


	GMT_LONG	current_factor;
	GMT_LONG	max_factor;
	GMT_LONG	n_factors = 0;
	GMT_LONG	two_four_toggle = 0;
	GMT_LONG	ten_twenty_toggle = 0;
	GMT_LONG	skip_five = 25;
	GMT_LONG	m;


	m = GMT_abs(n);
	if (m < 2) return(0);
	max_factor = (GMT_LONG)floor(sqrt((double)m));


	current_factor = 2;
	while(!(m%current_factor)) {
		m /= current_factor;
		f[n_factors] = (GMT_LONG)current_factor;
		n_factors++;
	}
	if (m == 1) return(n_factors);


	current_factor = 3;
	while(!(m%current_factor)) {
		m /= current_factor;
		f[n_factors] = (GMT_LONG)current_factor;
		n_factors++;
	}
	if (m == 1) return(n_factors);


	current_factor = 5;
	while(!(m%current_factor)) {
		m /= current_factor;
		f[n_factors] = (GMT_LONG)current_factor;
		n_factors++;
	}
	if (m == 1) return(n_factors);


	while (m > 1 && current_factor <= max_factor) {


		if (two_four_toggle) {
			current_factor += 4;
			two_four_toggle = 0;
		}
		else {
			current_factor += 2;
			two_four_toggle = 1;
		}


		if (current_factor == skip_five) {
			if (ten_twenty_toggle) {
				skip_five += 20;
				ten_twenty_toggle = 0;
			}
			else {
				skip_five += 10;
				ten_twenty_toggle = 1;
			}
			continue;
		}


		while(!(m%current_factor)) {
			m /= current_factor;
			f[n_factors] = (GMT_LONG)current_factor;
			n_factors++;
		}
	}


	if (m > 1) {

		f[n_factors] = (GMT_LONG)m;
		n_factors++;
	}
	return (n_factors);
}
