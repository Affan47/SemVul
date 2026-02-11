calc(int val) {
		int i;


		running_sum -= x[order-1];


		for(i = order-1; i > 0; i--) {
			x[i] = x[i-1];
		}
		x[0] = val;


		running_sum += x[0];


		return(running_sum);
	}
