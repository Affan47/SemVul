stopPlaying()
{

  ArLog::log(ArLog::Normal,
	     "ArSoundPlayer::stopPlaying: killing play and sox");


  int ret;

  if ((ret = system("killall play; killall -9 sox")) != -1)
  {
    ArLog::log(ArLog::Normal,
	       "ArSoundPlayer::stopPlaying: killed play and sox (got %d)",
	       ret);
    return;
  }
  else
  {
    ArLog::logErrorFromOS(ArLog::Normal,
			  "ArSoundPlayer::stopPlaying: system call failed");
    return;
  }


}
