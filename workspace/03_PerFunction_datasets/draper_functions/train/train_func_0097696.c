SetStackSize(SQInteger n)
{
	SQInteger size=_vlocals.size();
	while(size>n){
		size--;
		SQLocalVarInfo lvi=_vlocals.back();
		if(type(lvi._name)!=OT_NULL){
			lvi._end_op=GetCurrentPos();
			_localvarinfos.push_back(lvi);
		}
		_vlocals.pop_back();
	}
}
