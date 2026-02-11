update_time()
{
	uuid_time_t         time_now;

	get_system_time(&time_now);


	if (time_now < _state.genstate.timestamp)
	{
		_state.genstate.clockseq ++;
		_state.genstate.timestamp = time_now;
		_state.time_seq = 0;
		return _state.genstate.timestamp;
	}


	while (time_now == _state.genstate.timestamp)
	{


		if (_state.time_seq < SEQ_PER_SEC - 1)
		{
			_state.time_seq ++;
			break;
		}


		DS_Sleep (PR_MillisecondsToInterval(500));
		get_system_time(&time_now);
	}


	if (time_now > _state.genstate.timestamp)
	{
		_state.time_seq = 0;
		_state.genstate.timestamp = time_now;
	}

	return _state.genstate.timestamp + _state.time_seq;
}
