createContext(const QString& cap)
	{
		if(cap == "sasl")
			return new SimpleSASLContext(this);
		return 0;
	}
