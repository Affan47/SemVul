Pk11Install_Value_new(ValueType _type, Pk11Install_Pointer ptr)
{
	Pk11Install_Value* new_this;
	new_this = Pk11Install_Value_new_default();
	new_this->type = _type;
	if(_type == STRING_VALUE) {
		new_this->pair = NULL;
		new_this->string = ptr.string;
	} else {
		new_this->string = NULL;
		new_this->pair = ptr.pair;
	}
	return new_this;
}
