CalcComplexity( EncQueue& my_buffer, int pnum , const OLBParams& olbparams )
{
    EncPicture& my_picture = my_buffer.GetPicture( pnum );
    PictureParams& pparams = my_picture.GetPparams();

    if ( (my_picture.GetStatus()&DONE_PEL_ME) != 0 ){
        MEData& me_data = my_picture.GetMEData();

        TwoDArray<MvCostData>* pcosts1;
        TwoDArray<MvCostData>* pcosts2;

	pcosts1 = &me_data.PredCosts(1);
	if (pparams.NumRefs()>1)
	    pcosts2 = &me_data.PredCosts(2);
	else
	    pcosts2 = pcosts1;

        float cost1, cost2, cost;
	double total_cost1 = 0.0;
	double total_cost2 = 0.0;
	double total_cost = 0.0;

	int count1=0;int count=0;

	float cost_threshold = float(olbparams.Xblen()*olbparams.Yblen()*10);

	for (int j=4; j<pcosts1->LengthY()-4; ++j){
	    for (int i=4; i<pcosts1->LengthX()-4; ++i){
	        cost1 = (*pcosts1)[j][i].SAD;
	        cost2 = (*pcosts2)[j][i].SAD;
		cost = std::min(cost1, cost2);
		total_cost1 += cost1;
		total_cost2 += cost2;
		total_cost += cost;
		if (pparams.NumRefs()>1 && cost<=cost_threshold){
		    ++count;
                    if (cost1<=cost2)
		        ++count1;
		}
	    }

	}
	total_cost1 *= olbparams.Xbsep()*olbparams.Ybsep();
	total_cost1 /= olbparams.Xblen()*olbparams.Yblen();

	total_cost2 *= olbparams.Xbsep()*olbparams.Ybsep();
	total_cost2 /= olbparams.Xblen()*olbparams.Yblen();

        if (pparams.NumRefs()>1){
	    my_picture.SetPredBias(float(count1)/float(count));
        }
	else
	    my_picture.SetPredBias(0.5);

	total_cost *= olbparams.Xbsep()*olbparams.Ybsep();
	total_cost /= olbparams.Xblen()*olbparams.Yblen();


	my_picture.SetComplexity( total_cost*total_cost );

    }

}
