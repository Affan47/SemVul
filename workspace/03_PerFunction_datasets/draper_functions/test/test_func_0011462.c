SetDuration(TTime duration)
{
	CLAM_WARNING(false, "Audio::SetDuration is about to be deprecated. Please use Audio::ResizeToDuration instead");
	ResizeToDuration(GetIndexFromTime(duration));
}
