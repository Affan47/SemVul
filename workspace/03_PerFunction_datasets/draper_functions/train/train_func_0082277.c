operator=(BSON::Value && val){
	std::swap(_type,val._type);
	switch(_type){
		case BSON::UNDEFINED:
			break;
		case BSON::INT32:
			std::swap(_int32Value, val._int32Value);
			break;
		case BSON::INT64:
			std::swap(_int64Value, val._int64Value);
			break;
		case BSON::DOUBLE:
			std::swap(_doubleValue, val._doubleValue);
			break;
		case BSON::BOOL:
			std::swap(_boolValue, val._boolValue);
			break;
		case BSON::STRING:
			std::swap(_stringValue, val._stringValue);
			break;
		case BSON::BINARY:
			std::swap(_stringValue, val._stringValue);
			break;
		case BSON::DATETIME:
			std::swap(_datetimeValue, val._datetimeValue);
			break;
		case BSON::OBJECT:
			std::swap(_objectValue, val._objectValue);
			break;
		case BSON::ARRAY:
			std::swap(_arrayValue, val._arrayValue);
			break;
	}
	return *this;
}
