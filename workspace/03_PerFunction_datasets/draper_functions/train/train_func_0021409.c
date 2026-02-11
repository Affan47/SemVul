affect(u32 now, SParticle* particlearray, u32 count)
{
	if (!Enabled)
		return;
	f32 d;

	for (u32 i=0; i<count; ++i)
	{
		if (particlearray[i].endTime - now < FadeOutTime)
		{
			d = (particlearray[i].endTime - now) / FadeOutTime;
			particlearray[i].color = particlearray[i].startColor.getInterpolated(
				TargetColor, d);
		}
	}
}
