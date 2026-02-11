optimizeIncremental(int passes)
{
	if(passes<0) passes=m_leaves;
	if(m_root&&(passes>0))
	{
		do	{
			btDbvtNode*		node=m_root;
			unsigned	bit=0;
			while(node->isinternal())
			{
				node=sort(node,m_root)->childs[(m_opath>>bit)&1];
				bit=(bit+1)&(sizeof(unsigned)*8-1);
			}
			update(node);
			++m_opath;
		} while(--passes);
	}
}
