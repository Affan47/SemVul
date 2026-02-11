removeleaf(	btDbvt* pdbvt,
										   btDbvtNode* leaf)
{
	if(leaf==pdbvt->m_root)
	{
		pdbvt->m_root=0;
		return(0);
	}
	else
	{
		btDbvtNode*	parent=leaf->parent;
		btDbvtNode*	prev=parent->parent;
		btDbvtNode*	sibling=parent->childs[1-indexof(leaf)];
		if(prev)
		{
			prev->childs[indexof(parent)]=sibling;
			sibling->parent=prev;
			deletenode(pdbvt,parent);
			while(prev)
			{
				const btDbvtVolume	pb=prev->volume;
				Merge(prev->childs[0]->volume,prev->childs[1]->volume,prev->volume);
				if(NotEqual(pb,prev->volume))
				{
					prev=prev->parent;
				} else break;
			}
			return(prev?prev:pdbvt->m_root);
		}
		else
		{
			pdbvt->m_root=sibling;
			sibling->parent=0;
			deletenode(pdbvt,parent);
			return(pdbvt->m_root);
		}
	}
}
