Do(Audio &in)
	{
		TData scaleFactor = 0;


		if ( mType == 1 )
			scaleFactor = ComputeScaleFactorFromMaxEnergy( in.GetBuffer() );
		else if ( mType == 2 )
			scaleFactor = ComputeScaleFactorFromAvgEnergy( in.GetBuffer() );
		else if ( mType == 3 )
			scaleFactor = ComputeScaleFactorFromDominantEnergy( in.GetBuffer() );

		const TData invScaleFactor = 1.0 / scaleFactor;
		DataArray& inBufferSamples = in.GetBuffer();

		for (int n=0; n<in.GetSize(); n++)
			inBufferSamples[n]*=invScaleFactor;

		return true;
	}
