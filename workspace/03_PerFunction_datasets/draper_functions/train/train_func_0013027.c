BitwiseXorExp()
	{
		BitwiseAndExp();
		for(;;) if(_token == _SC('^'))
		{BIN_EXP(_OP_BITW, &SQCompiler::BitwiseAndExp,BW_XOR);
		}else return;
	}
