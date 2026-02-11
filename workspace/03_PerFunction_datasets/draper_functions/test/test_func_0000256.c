changeOdometry(const mrpt::poses::CPose2D &newOdometry)
{
#if MRPT_HAS_ARIA
	ArPose	pos_actual;

	THE_ROBOT->lock();
		pos_actual.setPose( newOdometry.x()*1000, newOdometry.y()*1000, RAD2DEG( newOdometry.phi() ) );
		THE_ROBOT->setDeadReconPose( pos_actual );
	THE_ROBOT->unlock();
#else
	MRPT_UNUSED_PARAM(newOdometry);
	THROW_EXCEPTION("MRPT has been compiled with 'MRPT_BUILD_ARIA'=OFF, so this class cannot be used.");
#endif
}
