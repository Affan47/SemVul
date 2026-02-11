findq(ino_t inum)
{
msgq	*qp=queuehashfirst[ inum % queuehashfirst.size() ];

	while (qp && qp->msgnum != inum)
		qp=qp->nexthash;
	return (qp);
}
