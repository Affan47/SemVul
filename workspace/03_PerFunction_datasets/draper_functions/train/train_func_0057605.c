reset()
	{
		delete encstate;
		encstate = 0;
		delete decstate;
		decstate = 0;

		console.stop();
		if(own_con)
		{
			delete con;
			con = 0;
			own_con = false;
		}
	}
