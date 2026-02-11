locarec_sizeof(locarec *l)
{
	u_long	tot = 0L;

	tot += sizeof(locarec);
	tot += l->city ? strlen(l->city)+1 : 0L;
	tot += l->state ? strlen(l->state)+1 : 0L;
	tot += l->country ? strlen(l->country)+1 : 0L;
	tot += l->addedby ? strlen(l->addedby)+1 : 0L;
	tot += l->description ? strlen(l->description)+1 : 0L;

	return tot;
}
