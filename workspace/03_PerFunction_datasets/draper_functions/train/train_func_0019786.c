ir_get_constructor_op(const TPublicType& type, TParseContext& ctx, bool allowStruct)
{
	TOperator op = EOpNull;
	switch (type.type) {
	case EbtFloat:
		op = ir_get_constructor_op_float(type, ctx);
		break;
	case EbtInt:
		switch(type.matrows) {
		case 1: op = EOpConstructInt;   break;
		case 2: op = EOpConstructIVec2; break;
		case 3: op = EOpConstructIVec3; break;
		case 4: op = EOpConstructIVec4; break;
		}
		break;
	case EbtBool:
		switch(type.matrows) {
		case 1: op = EOpConstructBool;  break;
		case 2: op = EOpConstructBVec2; break;
		case 3: op = EOpConstructBVec3; break;
		case 4: op = EOpConstructBVec4; break;
		}
		break;
	case EbtStruct:
		if (allowStruct)
			op = EOpConstructStruct;
		break;
	default:
		break;
	}
	return op;
}
