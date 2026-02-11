EnableMotors()
{
#if MRPT_HAS_ARIA
	THE_ROBOT->lock();
	if (!THE_ROBOT->areMotorsEnabled())
	{
			THE_ROBOT->enableMotors();
			cout << "[CActivMediaRobotBase] Enabling motors...";
	}
	THE_ROBOT->unlock();
#else
	THROW_EXCEPTION("MRPT has been compiled with 'MRPT_BUILD_ARIA'=OFF, so this class cannot be used.");
#endif
}
