setParticleSize(const core::dimension2d<f32> &size)
{
	os::Printer::log("setParticleSize is deprecated, use setMinStartSize/setMaxStartSize in emitter.", irr::ELL_WARNING);

	if (Emitter)
	{
		Emitter->setMinStartSize(size);
		Emitter->setMaxStartSize(size);
	}
	ParticleSize = size;
}
