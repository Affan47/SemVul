asn_free_sequence(struct asn_node *nd)
{
	struct  asn_node  *nxt;

	do  {
		if  (nd->asn_firstchild)
			asn_free_sequence(nd->asn_firstchild);
		nxt = nd->asn_next;
		asn_nodefree(nd);
		nd = nxt;
	}  while  (nd);
}
