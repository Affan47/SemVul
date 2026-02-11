ConcreteStart()
	{
		if (!mAmplitudeAverages.Configured())
			return false;

		mAmplitudeAverages.Clear();

		int i,n_interp_points;

		if (mIsSpline) n_interp_points = mPointsPerFrame + 3;
		else           n_interp_points = mPointsPerFrame + 1;
		for (i=0; i<n_interp_points; i++)
			mInterpolationPoints[i]=0.0;

		return true;
	}
