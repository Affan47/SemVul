create(JDnsGlobal *global, Mode mode, QObject *parent = 0)
	{
		if(mode == Internet)
		{
			if(!global->ensure_uni_net())
				return 0;
		}
		else
		{
			if(!global->ensure_uni_local())
				return 0;
		}

		return new JDnsNameProvider(global, mode, parent);
	}
