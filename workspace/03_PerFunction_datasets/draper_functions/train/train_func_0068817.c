SetIntegrationLength(TTime length)
	{
		int memory_points = int(length / mInterpolationPeriod);

		if (memory_points <= 0)
			return false;

		mIntegrationLength = length;

		SetNMemoryPoints(memory_points);

		return true;
	}
