opj_lupInvert (OPJ_FLOAT32 * pSrcMatrix,
                    OPJ_FLOAT32 * pDestMatrix,
                    OPJ_UINT32 nb_compo,
                    OPJ_UINT32 * pPermutations,
                    OPJ_FLOAT32 * p_src_temp,
                    OPJ_FLOAT32 * p_dest_temp,
                    OPJ_FLOAT32 * p_swap_area )
{
	OPJ_UINT32 j,i;
	OPJ_FLOAT32 * lCurrentPtr;
	OPJ_FLOAT32 * lLineMatrix = pDestMatrix;
	OPJ_UINT32 lSwapSize = nb_compo * sizeof(OPJ_FLOAT32);

	for (j = 0; j < nb_compo; ++j) {
		lCurrentPtr = lLineMatrix++;
        memset(p_src_temp,0,lSwapSize);
    	p_src_temp[j] = 1.0;
		opj_lupSolve(p_dest_temp,pSrcMatrix,p_src_temp, pPermutations, nb_compo , p_swap_area);

		for (i = 0; i < nb_compo; ++i) {
    		*(lCurrentPtr) = p_dest_temp[i];
			lCurrentPtr+=nb_compo;
    	}
    }
}
