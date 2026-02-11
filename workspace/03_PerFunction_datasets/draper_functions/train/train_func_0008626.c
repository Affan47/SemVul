patchFeatures()
{
	if (type() == PostScript || type() == Pdf)
	{
		QPaintEngine::PaintEngineFeatures f = QPaintEngine::AllFeatures;
		f &= (QPaintEngine::PorterDuff | QPaintEngine::PerspectiveTransform
						| QPaintEngine::ObjectBoundingModeGradients
						| QPaintEngine::LinearGradientFill
						| QPaintEngine::RadialGradientFill
						| QPaintEngine::ConicalGradientFill);

		gccaps = f;
	}
}
