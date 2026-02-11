Replace2(unsigned int pos,TWordID id,TWordID id2)
{
	if((!IsValid())||(id==0)||(AssertIfProtected())) return(0);
	unsigned int size=Size();
	if(pos<size) {
		return Replace(pos,id);
	}else{
		for(unsigned int i=size; i<pos; i++){
			Push(id2);
		}
		Push(id);
		return 0;
	}
}
