addDataExprToHeap ( TDataEntry* p )
{
	if ( isValid(p->getBP()) )
		return p->getBP();


	DagTag dt = p->isBasicDataType() ? dtDataType : p->isDataValue() ? dtDataValue : dtDataExpr;
	BipolarPointer hostBP = bpTOP;


	if ( p->getType() != NULL )
		hostBP = addDataExprToHeap(const_cast<TDataEntry*>(p->getType()));


	DLVertex* ver = new DLVertex ( dt, hostBP );
	ver->setConcept(p);
	p->setBP(DLHeap.directAdd(ver));

	return p->getBP();
}
