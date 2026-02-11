auxiliarComputeObservationLikelihood(
	const bayes::CParticleFilter::TParticleFilterOptions &PF_options,
	const CParticleFilterCapable	*obj,
	size_t			particleIndexForMap,
	const CSensoryFrame	*observation,
	const CPose2D			*x )
{
	MRPT_UNUSED_PARAM(PF_options);
	const CLocalMetricHypothesis  *theObj = static_cast<const CLocalMetricHypothesis*>(obj);
	CMultiMetricMap			*map = &theObj->m_particles[particleIndexForMap].d->metricMaps;

	return map->computeObservationsLikelihood( *observation, *x );
}
