Get(const SQObjectPtr &self,const SQObjectPtr &key,SQObjectPtr &dest,bool raw, bool fetchroot)
{
	switch(type(self)){
	case OT_TABLE:
		if(_table(self)->Get(key,dest))return true;
		break;
	case OT_ARRAY:
		if(sq_isnumeric(key)){
			return _array(self)->Get(tointeger(key),dest);
		}
		break;
	case OT_INSTANCE:
		if(_instance(self)->Get(key,dest)) return true;
		break;
	default:break;
	}
	if(FallBackGet(self,key,dest,raw)) return true;

	if(fetchroot) {
		if(_rawval(STK(0)) == _rawval(self) &&
			type(STK(0)) == type(self)) {
				return _table(_roottable)->Get(key,dest);
		}
	}
	return false;
}
