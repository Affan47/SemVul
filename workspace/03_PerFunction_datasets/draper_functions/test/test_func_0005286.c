precomputeConfigs()
	{
		_precomputedConfigs.clear();

		short x, y, w, h;
		size_t numConfigs = 0;


		for (x = 0; x < HaarData::areaWidth(); ++x)
		{

			for (y = 0; y < HaarData::areaHeight(); ++y)
			{
				for (w = _width-1; w < HaarData::areaWidth() - x; w = w + _width)
				{
					for (h = _height-1; h < HaarData::areaHeight() - y; h = h + _height)
						++numConfigs;
				}
			}
		}

		_precomputedConfigs.reserve(numConfigs);


		for (x = 0; x < HaarData::areaWidth(); ++x)
		{

			for (y = 0; y < HaarData::areaHeight(); ++y)
			{
				for (w = _width-1; w < HaarData::areaWidth() - x; w = w + _width)
				{
					for (h = _height-1; h < HaarData::areaHeight() - y; h = h + _height)
						_precomputedConfigs.push_back( nor_utils::Rect(x, y, w, h) );
				}
			}
		}

		_configIt = _precomputedConfigs.begin();
		_visitedConfigs.resize(_precomputedConfigs.size());
		return static_cast<int>(_precomputedConfigs.size());
	}
