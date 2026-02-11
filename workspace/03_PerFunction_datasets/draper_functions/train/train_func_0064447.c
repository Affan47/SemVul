eval_qa_series_aux (uintC N1, uintC N2,
                                const cl_qa_series& args,
                                cl_I* Q, cl_I* T)
{
	switch (N2 - N1) {
	case 0:
		throw runtime_exception(); break;
	case 1:
		*Q = args.qv[N1];
		*T = args.av[N1];
		break;
	case 2: {
		*Q = args.qv[N1] * args.qv[N1+1];
		*T = args.qv[N1+1] * args.av[N1]
		   + args.av[N1+1];
		break;
		}
	case 3: {
		var cl_I q12 = args.qv[N1+1] * args.qv[N1+2];
		*Q = args.qv[N1] * q12;
		*T = q12 * args.av[N1]
		   + args.qv[N1+2] * args.av[N1+1]
		   + args.av[N1+2];
		break;
		}
	case 4: {
		var cl_I q23 = args.qv[N1+2] * args.qv[N1+3];
		var cl_I q123 = args.qv[N1+1] * q23;
		*Q = args.qv[N1] * q123;
		*T = q123 * args.av[N1]
		   + q23 * args.av[N1+1]
		   + args.qv[N1+3] * args.av[N1+2]
		   + args.av[N1+3];
		break;
		}
	default: {
		var uintC Nm = (N1+N2)/2;

		var cl_I LQ, LT;
		eval_qa_series_aux(N1,Nm,args,&LQ,&LT);

		var cl_I RQ, RT;
		eval_qa_series_aux(Nm,N2,args,&RQ,&RT);

		*Q = LQ*RQ;

		*T = RQ*LT + RT;
		break;
		}
	}
}
