operator- (const cl_I& x)
{
	if (fixnump(x)) {
		#if (cl_value_len < intVsize)
		return V_to_I(- FN_to_V(x));
		#elif (cl_word_size==64)
		return Q_to_I(- FN_to_Q(x));
		#elif (intVsize==32)
		var sint32 xhi = sign_of(FN_to_V(x));
		var uint32 xlo = FN_to_V(x);
		return L2_to_I(-xhi-(xlo!=0),-xlo);
		#endif
	} else {

          CL_ALLOCA_STACK;
          var uintD* MSDptr;
          var uintC len;
          var uintD* LSDptr;
          BN_to_NDS_1(x, MSDptr=,len=,LSDptr=);

          { var sintD sign = sign_of_sintD(mspref(MSDptr,0));
            lsprefnext(MSDptr) = sign; len++;
          }

          neg_loop_lsp(LSDptr,len);

          return DS_to_I(MSDptr,len);
	}
}

}
