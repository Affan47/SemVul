createFollowSplineAnimator(s32 startTime,
	const core::array< core::vector3df >& points,
	f32 speed, f32 tightness, bool loop, bool pingpong)
{
	ISceneNodeAnimator* a = new CSceneNodeAnimatorFollowSpline(startTime, points,
		speed, tightness, loop, pingpong);
	return a;
}
