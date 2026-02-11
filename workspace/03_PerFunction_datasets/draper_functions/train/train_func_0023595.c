playback_when(playback_ty *pbp)
{
    if (!pbp || !pbp->clp)
	return time_max();
    if (pbp->position >= pbp->clp->length)
    {
	change::pointer cp = pbp->pp->change_get();
	return change_completion_timestamp(cp);
    }
    return change_completion_timestamp(pbp->clp->item[pbp->position]);
}
