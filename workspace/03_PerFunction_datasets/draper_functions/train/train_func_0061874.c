drawTree(	btIDebugDraw* idraw,
								 const btDbvtNode* node,
								 int depth,
								 const btVector3& ncolor,
								 const btVector3& lcolor,
								 int mindepth,
								 int maxdepth)
{
	if(node)
	{
		if(node->isinternal()&&((depth<maxdepth)||(maxdepth<0)))
		{
			drawTree(idraw,node->childs[0],depth+1,ncolor,lcolor,mindepth,maxdepth);
			drawTree(idraw,node->childs[1],depth+1,ncolor,lcolor,mindepth,maxdepth);
		}
		if(depth>=mindepth)
		{
			const btScalar	scl=(btScalar)(node->isinternal()?1:1);
			const btVector3	mi=node->volume.Center()-node->volume.Extents()*scl;
			const btVector3	mx=node->volume.Center()+node->volume.Extents()*scl;
			drawBox(idraw,mi,mx,node->isleaf()?lcolor:ncolor);
		}
	}
}
