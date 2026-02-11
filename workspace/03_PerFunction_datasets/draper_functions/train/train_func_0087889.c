write(IWriter* iwriter) const
{
	btDbvtNodeEnumerator	nodes;
	nodes.nodes.reserve(m_leaves*2);
	enumNodes(m_root,nodes);
	iwriter->Prepare(m_root,nodes.nodes.size());
	for(int i=0;i<nodes.nodes.size();++i)
	{
		const btDbvtNode* n=nodes.nodes[i];
		int			p=-1;
		if(n->parent) p=nodes.nodes.findLinearSearch(n->parent);
		if(n->isinternal())
		{
			const int	c0=nodes.nodes.findLinearSearch(n->childs[0]);
			const int	c1=nodes.nodes.findLinearSearch(n->childs[1]);
			iwriter->WriteNode(n,i,p,c0,c1);
		}
		else
		{
			iwriter->WriteLeaf(n,i,p);
		}
	}
}
