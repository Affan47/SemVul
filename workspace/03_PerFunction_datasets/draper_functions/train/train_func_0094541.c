edialign_rel_wgt_calc(ajint l1, ajint l2, float **rel_wgt)
{
    ajint l;
    ajint m;
    ajint mss = 0;
    float ent;
    float factor;
    float l1f;
    float l2f;
    float av_sim_score = 0.;
    double t_pr;
    double pr400;
    double **tpr = NULL;


    if( rel_wgt == wgt_prot )
    {
	tpr = tp400_prot ;
	mss = max_sim_score ;
	av_sim_score = av_sim_score_pep ;
    }

    if( rel_wgt == wgt_dna )
    {
	tpr = tp400_dna ;
	mss = 1 ;
	av_sim_score = av_sim_score_nuc ;
    }

    if( rel_wgt == wgt_trans )
    {
	tpr = tp400_trans ;
	mss = max_sim_score ;
	av_sim_score = av_sim_score_pep ;
    }


    l1f = (float) l1;
    l2f = (float) l2;

    factor = ( l1f * l2f ) / (float) 400.00;


    for( l = 1 ; l <= max_dia; l++ )
	for( m = 0 ; m <= l * mss ; m++ )
	{
	    rel_wgt[l][m] = 0;


	    if( tpr[l][m] )
		if( m > av_sim_score * l )

		{
		    pr400 = tpr[l][m];

		    if( pr400 > 0.0000000001 )
			t_pr = 1 - pow( 1 - pr400 , factor );
		    else
			t_pr = pr400 * factor;

		    ent = 0;

		    if(t_pr)
		      ent = (float) -log( t_pr );

		    if( ent > threshold )
			rel_wgt[l][m] = ent;
		}
	}

    return;
}
