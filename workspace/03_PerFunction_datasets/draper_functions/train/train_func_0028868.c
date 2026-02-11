ConcreteConfigure(const ProcessingConfig& c)
	{
		CopyAsConcreteConfig(mConfig, c);

		mIsSpline = (mConfig.GetInterpolationType() == EInterpolation::eSpline);

		mFrameSize = mConfig.GetFrameSize();

		if (!mFrameSize)
		{
			AddConfigErrorMessage("FrameSize must be non-zero");
			return false;
		}

		mFrameTime = 1000.0 * double(mFrameSize) / double(mConfig.GetSampleRate());

		if (mConfig.GetNInterpPointsPerFrame() > 0)
		{
			SetPointsPerFrame(mConfig.GetNInterpPointsPerFrame());
		}
		else if (mConfig.GetInterpolationPeriod().GetInitValue() > 0.0)
		{
			if (!SetInterpolationPeriod(mConfig.GetInterpolationPeriod().GetInitValue()))
			{
				AddConfigErrorMessage("The interpolation period requested in config would require\n"
				           "less than one interpolation point per frame");
				return false;
			}
		}
		else {
			AddConfigErrorMessage("Neither the number of interpolation points per frame nor the \n"
			           "interpolation period requested in configuration are valid.");
			return false;
		}

		if (mConfig.GetNMemoryPoints() > 0 )
		{
			SetNMemoryPoints(mConfig.GetNMemoryPoints());
		}
		else if ( mConfig.GetIntegrationLength().GetInitValue() > 0.0  )
		{
			if (!SetIntegrationLength(mConfig.GetIntegrationLength().GetInitValue()))
			{
				AddConfigErrorMessage("The integration length requested leads"
				           "to a non-positive number of memory points.");
				return false;
			}
		}
		else
		{
			AddConfigErrorMessage("Neither the integration length nor the number of memory points"
			           "requested in configuration are valid.");
			return false;
		}

		SetNormalLevel(mConfig.GetNormalLevel().GetInitValue());

		SetSilenceLevel(mConfig.GetSilenceLevel().GetInitValue());

		mSampleDelta = 1000.0 / (TTime)mConfig.GetSampleRate();

		mDeltaX = (mSampleDelta * TTime(mFrameSize)) / TTime(mPointsPerFrame);

		InitializeControls();

		Input.SetSize(mFrameSize);
		return true;
	}
