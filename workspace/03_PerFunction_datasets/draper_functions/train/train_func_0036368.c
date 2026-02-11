FirstPredXact(void)
{
	PredXactListElement ptle;

	ptle = (PredXactListElement)
		SHMQueueNext(&PredXact->activeList,
					 &PredXact->activeList,
					 offsetof(PredXactListElementData, link));
	if (!ptle)
		return NULL;

	return &ptle->sxact;
}
