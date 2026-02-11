provideRewardForBanditAlgo()
	{
		string key = getKeyToString();
		_banditAlgo->receiveReward( key, _reward );
	}
