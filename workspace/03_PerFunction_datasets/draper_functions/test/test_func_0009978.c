icp_test_1(int a1, int a2)
{
#ifdef MRPT_DATASET_DIR
	const string rawlog_file = MRPT_DATASET_DIR  "/2006-01ENE-21-SENA_Telecom Faculty_one_loop_only.rawlog";
	if (!mrpt::system::fileExists(rawlog_file))
		return 1;

	CTicTac	 tictac;

	int			step = 0;
	size_t		rawlogEntry = 0;
	CFileGZInputStream	rawlogFile( rawlog_file );

	TSetOfMetricMapInitializers  metricMapsOpts;

	const bool use_grid = a1!=0;

	if (use_grid)
	{
		COccupancyGridMap2D::TMapDefinition def;
		def.resolution = 0.05;
		metricMapsOpts.push_back( def );
	}
	else
	{
		CSimplePointsMap::TMapDefinition def;
		def.insertionOpts.minDistBetweenLaserPoints = 0.03;
		metricMapsOpts.push_back( def );
	}

	double insertionLinDistance = 0.75;
	double insertionAngDistance = DEG2RAD(30);

	CICP::TConfigParams  icpOptions;

	icpOptions.maxIterations = 40;


	CMetricMapBuilderICP mapBuilder;

	mapBuilder.ICP_options.mapInitializers = metricMapsOpts;

	mapBuilder.ICP_options.insertionLinDistance = insertionLinDistance;
	mapBuilder.ICP_options.insertionAngDistance = insertionAngDistance;

	mapBuilder.ICP_options.matchAgainstTheGrid = use_grid ;
	mapBuilder.ICP_params = icpOptions;


	mapBuilder.initialize( CSimpleMap() );


	mapBuilder.options.verbose					= false;
	mapBuilder.options.enableMapUpdating		= true;


	CActionCollectionPtr	action;
	CSensoryFramePtr		observations;

	for (;;)
	{


		if (! CRawlog::readActionObservationPair( rawlogFile, action, observations, rawlogEntry) )
			break;


		mapBuilder.processActionObservation( *action, *observations );

		step++;


		action.clear_unique();
		observations.clear_unique();
	}

#if 0
	mapBuilder.getCurrentlyBuiltMetricMap()->saveMetricMapRepresentationToFile( format("icp_%i_result",a1) );
#endif

	if (!step) step++;

	return tictac.Tac()/step;
#else
	return 1;
#endif
}
