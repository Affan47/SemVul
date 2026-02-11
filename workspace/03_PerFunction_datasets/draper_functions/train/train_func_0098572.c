_Refit(AABBTreeBuilder* builder)
{

	builder->ComputeGlobalBox(mNodePrimitives, mNbPrimitives, mBV);


	AABBTreeNode* Pos = (AABBTreeNode*)GetPos();
	AABBTreeNode* Neg = (AABBTreeNode*)GetNeg();
	if(Pos)	Pos->_Refit(builder);
	if(Neg)	Neg->_Refit(builder);
}
