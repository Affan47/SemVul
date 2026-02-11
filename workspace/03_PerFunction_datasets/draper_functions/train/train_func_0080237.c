fastDrawSingleSample( CPose2D &outSample )const
{


	if (estimationMethod== emOdometry)
	{
		if ( motionModelConfiguration.modelSelection == mmGaussian )
				fastDrawSingleSample_modelGaussian( outSample );
		else	fastDrawSingleSample_modelThrun( outSample );
	}
	else
	{

		poseChange->drawSingleSample( outSample );
	}
}
