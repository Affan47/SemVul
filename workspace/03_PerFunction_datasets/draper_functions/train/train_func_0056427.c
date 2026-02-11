Do(Frame& in)
{
	InitFrame(in);


	in.GetSpectrum().SetSize(mConfig.GetSinSpectralAnalysis().GetFFT().GetAudioSize()/2+1);
	in.GetFundamental().SetnMaxCandidates(1);

	bool result=false;

	if(mAudioProvider.CanProduce())
	{

		mAudioProvider.SetSampleRate( in.GetAudioFrame().GetSampleRate() );
		mAudioProvider.GetAudio().GetBuffer() = in.GetAudioFrame().GetBuffer();
		mAudioProvider.Produce();
	}

	if(mCore.CanConsumeAndProduce())
		result = mCore.Do();
	else
		return false;

	OutPortBase & outSinSpectrum  = mCore.GetOutPort("Sinusoidal Branch Spectrum");
	in.GetSinusoidalAnalSpectrum() =  dynamic_cast<OutPortPublisher<Spectrum>&>(outSinSpectrum).GetLastWrittenData();

	OutPortBase & outResSpectrum  = mCore.GetOutPort("Residual Spectrum");
	in.GetResidualSpec() =  dynamic_cast<OutPortPublisher<Spectrum>&>(outResSpectrum).GetLastWrittenData();

	OutPortBase & outSpectrum  = mCore.GetOutPort("Residual Branch Spectrum");
	in.GetSpectrum() =  dynamic_cast<OutPortPublisher<Spectrum>&>(outSpectrum).GetLastWrittenData();

	OutPortBase & fundamental  = mCore.GetOutPort("Fundamental");
	in.GetFundamental() =  dynamic_cast<OutPortPublisher<Fundamental>&>(fundamental).GetLastWrittenData();

	OutPortBase & peaks  = mCore.GetOutPort("Sinusoidal Peaks");
	in.GetSpectralPeakArray() = dynamic_cast<OutPortPublisher<SpectralPeakArray>&>(peaks).GetLastWrittenData();


	CLAM_DEBUG_ASSERT( in.GetResidualSpec().GetSpectralRange() > 0,
			   "Residual spectrum is not being properly configured" );

	if (result)

		in.SetIsHarmonic(in.GetFundamental().GetFreq(0)>0);
	return result;
}
