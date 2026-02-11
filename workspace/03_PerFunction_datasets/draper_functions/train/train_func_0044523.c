getArgs(const nor_utils::Args& args)
	{
		AdaBoostMHLearner::getArgs( args );

		if ( args.hasArgument("Cn") )
		{
			args.getValue("Cn", 0, _Cn);
			if (_verbose > 1)
				cout << "--> Resampling size: " << _Cn << endl;
		}

		if ( args.hasArgument("onlinetraining") )
		{
			_onlineWeakLearning = true;
		}
	}
