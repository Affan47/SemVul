OnAnimate(u32 timeMs)
{
    if(!SoundFileNames.size())
        return;

	ISceneNode::OnAnimate(timeMs);


	core::vector3df pos = getAbsolutePosition();

	if (Sound)
		Sound->setPosition(pos);

	switch(PlayMode)
	{
	case EPM_NOTHING:
		return;
	case EPM_RANDOM:
		{
			if (Sound && Sound->isFinished())
			{
				Sound->drop();
				Sound = 0;


				s32 delta = MaxTimeMsInterval - MinTimeMsInterval;

				if (delta < 2)
					delta = 2;

				TimeMsDelayFinished = timeMs + (rand()%delta) + MinTimeMsInterval;
			}
			else
			if (!Sound && (!TimeMsDelayFinished || timeMs > TimeMsDelayFinished))
			{

                core::stringc& SoundFileName = SoundFileNames[ rand() % SoundFileNames.size() ];

				if (SoundFileName.size())
					Sound = SoundEngine->play3D(SoundFileName.c_str(), pos, false, true, true);

				if (Sound)
				{
					if (MinDistance > 0 )
						Sound->setMinDistance(MinDistance);
					if (MaxDistance > 0 )
						Sound->setMaxDistance(MaxDistance);

					Sound->setIsPaused(false);
				}
			}
		}
		break;
	case EPM_LOOPING:
		{
			if (!Sound)
			{
                core::stringc& SoundFileName = SoundFileNames[ rand() % SoundFileNames.size() ];
				if (SoundFileName.size())
					Sound = SoundEngine->play3D(SoundFileName.c_str(), pos, true, true, true);

				if (Sound)
				{
					if (MinDistance > 0 )
						Sound->setMinDistance(MinDistance);
					if (MaxDistance > 0 )
						Sound->setMaxDistance(MaxDistance);

					Sound->setIsPaused(false);
				}
				else
				{

					stop();
				}
			}
		}
		break;
	case EPM_ONCE:
		{
			if (PlayedCount)
			{


				if (Sound && Sound->isFinished())
				{
					stop();

					if (DeleteWhenFinished)
						SceneManager->addToDeletionQueue(this);
				}
			}
			else
			{

                core::stringc& SoundFileName = SoundFileNames[ rand() % SoundFileNames.size() ];

				if (SoundFileName.size())
					Sound = SoundEngine->play3D(SoundFileName.c_str(), pos, false, true, true);

				if (Sound)
				{
					if (MinDistance > 0 )
						Sound->setMinDistance(MinDistance);
					if (MaxDistance > 0 )
						Sound->setMaxDistance(MaxDistance);

					Sound->setIsPaused(false);
					++PlayedCount;
				}
				else
				{

					stop();
				}
			}
		}
		break;
	}
}
