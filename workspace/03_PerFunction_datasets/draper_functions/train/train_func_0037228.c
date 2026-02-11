dumpToTextStream(mrpt::utils::CStream	&out) const
{
	out.printf("\n----------- [COccupancyGridMap2D::TLikelihoodOptions] ------------ \n\n");

	out.printf("likelihoodMethod                        = ");
	switch (likelihoodMethod)
	{
	case lmMeanInformation: out.printf("lmMeanInformation"); break;
	case lmRayTracing: out.printf("lmRayTracing"); break;
	case lmConsensus: out.printf("lmConsensus"); break;
	case lmCellsDifference: out.printf("lmCellsDifference"); break;
	case lmLikelihoodField_Thrun: out.printf("lmLikelihoodField_Thrun"); break;
	case lmLikelihoodField_II: out.printf("lmLikelihoodField_II"); break;
	case lmConsensusOWA: out.printf("lmConsensusOWA"); break;
	default:
		out.printf("UNKNOWN!!!"); break;
	}
	out.printf("\n");

	out.printf("enableLikelihoodCache                   = %c\n",	enableLikelihoodCache ? 'Y':'N');

	out.printf("LF_stdHit                               = %f\n",	LF_stdHit );
	out.printf("LF_zHit                                 = %f\n",	LF_zHit );
	out.printf("LF_zRandom                              = %f\n",	LF_zRandom );
	out.printf("LF_maxRange                             = %f\n",	LF_maxRange );
	out.printf("LF_decimation                           = %u\n",	LF_decimation );
	out.printf("LF_maxCorrsDistance                     = %f\n",	LF_maxCorrsDistance );
	out.printf("LF_useSquareDist                        = %c\n",	LF_useSquareDist ? 'Y':'N');
	out.printf("LF_alternateAverageMethod               = %c\n",	LF_alternateAverageMethod ? 'Y':'N');
	out.printf("MI_exponent                             = %f\n",	MI_exponent );
	out.printf("MI_skip_rays                            = %u\n",	MI_skip_rays );
	out.printf("MI_ratio_max_distance                   = %f\n",	MI_ratio_max_distance );
	out.printf("rayTracing_useDistanceFilter            = %c\n",	rayTracing_useDistanceFilter ? 'Y':'N');
	out.printf("rayTracing_decimation                   = %u\n",	rayTracing_decimation );
	out.printf("rayTracing_stdHit                       = %f\n",	rayTracing_stdHit );
	out.printf("consensus_takeEachRange                 = %u\n",	consensus_takeEachRange );
	out.printf("consensus_pow                           = %.02f\n", consensus_pow);
	out.printf("OWA_weights   = [");
	for (size_t i=0;i<OWA_weights.size();i++)
	{
		if (i<3 || i>(OWA_weights.size()-3))
			out.printf("%.03f ",OWA_weights[i]);
		else if (i==3 && OWA_weights.size()>6)
			out.printf(" ... ");
	}
	out.printf("] (size=%u)\n",(unsigned)OWA_weights.size());
	out.printf("\n");
}
