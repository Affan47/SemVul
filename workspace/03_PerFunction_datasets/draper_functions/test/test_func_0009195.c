CreateMultiCurve() const
{
	FloatList defaultValues;
	size_t count = values.size();
	defaultValues.resize(count);
	for (size_t i = 0; i < count; ++i) defaultValues[i] = (*values[i]);

	fm::pvector<const FCDAnimationCurve> toMerge;
	toMerge.resize(count);
	for (size_t i = 0; i < count; ++i) toMerge[i] = (!curves[i].empty()) ? curves[i][0] : NULL;
	return FCDAnimationCurveTools::MergeCurves(toMerge, defaultValues);
}
