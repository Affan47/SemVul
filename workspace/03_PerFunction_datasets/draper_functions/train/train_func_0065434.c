CheckSilence( int size )
	{
		if (size==0)
			mIsSilenceCtrl.SendControl(true);
		else
			mIsSilenceCtrl.SendControl(false);
	}


}
