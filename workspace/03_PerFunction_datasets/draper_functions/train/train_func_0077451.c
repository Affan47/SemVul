recip2adic (uintC len, const uintD* a_LSDptr, uintD* dest_LSDptr)
{


	CL_ALLOCA_STACK;
	var uintL k = 0;
	var uintC n = len;
	while (n >= recip2adic_threshold) {
		n = ceiling(n,2);
		k++;
	}

	var uintD* one_LSDptr;
	num_stack_alloc(n,,one_LSDptr=);
	lspref(one_LSDptr,0) = 1;
	clear_loop_lsp(one_LSDptr lspop 1,n-1);
	div2adic(n,one_LSDptr,a_LSDptr,dest_LSDptr);

	if (k > 0) {
		var uintD* b2_LSDptr;
		var uintD* prod_LSDptr;
		num_stack_alloc(len+1,,b2_LSDptr=);
		num_stack_alloc(2*len,,prod_LSDptr=);
		do {


			k--;
			var uintC n2 = ((len-1)>>k)+1;

			cl_UDS_mul_square(dest_LSDptr,n,b2_LSDptr);
			cl_UDS_mul(b2_LSDptr,n2,a_LSDptr,n2,prod_LSDptr);
			clear_loop_lsp(dest_LSDptr lspop n,n2-n);
			shift1left_loop_lsp(dest_LSDptr,n+1);
			subfrom_loop_lsp(prod_LSDptr,dest_LSDptr,n2);
			n = n2;
		} while (k > 0);
	}
}
