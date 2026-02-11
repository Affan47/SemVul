createPointEmitter(
	const core::vector3df& direction, u32 minParticlesPerSecond,
	u32 maxParticlesPerSecond, const video::SColor& minStartColor,
	const video::SColor& maxStartColor, u32 lifeTimeMin, u32 lifeTimeMax,
	s32 maxAngleDegrees, const core::dimension2df& minStartSize,
	const core::dimension2df& maxStartSize )
{
	return new CParticlePointEmitter(direction, minParticlesPerSecond,
		maxParticlesPerSecond, minStartColor, maxStartColor,
		lifeTimeMin, lifeTimeMax, maxAngleDegrees,
			minStartSize, maxStartSize );
}
