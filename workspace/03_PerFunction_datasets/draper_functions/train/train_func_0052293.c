getNewIndex() const
	{

		for(int n = 0;; ++n)
		{
			bool found = false;
			foreach(Instance *i, instances)
			{
				if(i->index == n)
				{
					found = true;
					break;
				}
			}
			if(!found)
				return n;
		}
	}
