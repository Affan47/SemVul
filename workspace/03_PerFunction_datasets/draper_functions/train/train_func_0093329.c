gf_smil_timing_is_active(GF_Node *node)
{
	SMILTimingAttributesPointers *timingp = NULL;
	timingp = ((SVGTimedAnimBaseElement *)node)->timingp;
	if (!timingp || !timingp->runtime) return 0;
	return (timingp->runtime->status == SMIL_STATUS_ACTIVE);
}
