CopyFrom(const TreeValue* v)
	{
		const TreeBinary* src = TreeValueCast<TreeBinary> (v);
		if (src != NULL)
		{
			delete binmemory;
			binmemory = src->binmemory->Clone();
		}
	}
