reset()
	{
		delete dec;
		dec = 0;
		in.resize(0);
		out = "";
		at = 0;
		paused = false;
		mightChangeEncoding = true;
		checkBad = true;
		last = QChar();
		v_encoding = "";
		resetLastData();
	}
