mrows (header *hd)
{	header *st=hd,*res;
	int n;
	hd=getvalue(hd); if (error) return;
	switch (hd->type)
	{	case s_matrix :
		case s_cmatrix :
		case s_imatrix : n=dimsof(hd)->r; break;
		case s_submatrix :
		case s_csubmatrix :
		case s_isubmatrix : n=submdimsof(hd)->r; break;
		case s_real :
		case s_complex :
		case s_interval : n=1; break;
		default : wrong_arg_in("rows");
	}
	res=new_real(n,""); if (error) return;
	moveresult(st,res);
}
