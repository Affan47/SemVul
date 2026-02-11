SetKeyframe(SpectFrame *sf, int yes)
{
	if(sf->keyframe == yes) return;

	sf->keyframe = yes;
	pitchgraph->Refresh();

	WriteDialogLength();
}
