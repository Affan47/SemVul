traverse(CXMLElementVisitor& inoutVisitor)const{

    if(inoutVisitor.startVisit(*this)){
	if(mChildren.size()){
	    for(lCChildren::const_iterator i=mChildren.begin();
		i!=mChildren.end();
		i++){
		(*i)->traverse(inoutVisitor);
	    }
	}
	inoutVisitor.endVisit(*this);
    }
}
