get_overlap_element_num(int *pCurrRange[],
			int *pTargetRange[],
			int  maxDim)
{
    int num = 1, i, start, end;

    for(i = 0; i < maxDim; i++){
	start = ((pCurrRange[0][i] > pTargetRange[0][i])?
		 pCurrRange[0][i] : pTargetRange[0][i]);

	end   = ((pCurrRange[1][i] < pTargetRange[1][i])?
		 pCurrRange[1][i] : pTargetRange[1][i]);

	num *= ((end-start+1) <= 0) ? 0 : (end-start+1);
    }
    return(num);
}
