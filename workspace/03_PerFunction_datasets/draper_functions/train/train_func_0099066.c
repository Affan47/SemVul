ConcreteCompute()
{
	if (HasMean())
		SetMean(mpStats->GetMean());
	if (HasTemporalCentroid())
		SetTemporalCentroid(mpStats->GetCentroid()/mpAudio->GetSampleRate());
	if (HasEnergy())
		SetEnergy(mpStats->GetEnergy());
	if(HasVariance())
		SetVariance(mpStats->GetVariance());
	if(HasZeroCrossingRate())
		SetZeroCrossingRate(ComputeZeroCrossingRate());
	if(HasRiseTime())
		SetRiseTime(ComputeAttackTime());
	if(HasLogAttackTime())
		SetLogAttackTime(ComputeLogAttackTime());
	if(HasDecrease())
		SetDecrease(ComputeDecrease());
}
