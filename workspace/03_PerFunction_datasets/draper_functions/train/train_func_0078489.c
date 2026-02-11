ir_get_constructor_op_float(const TPublicType& t, TParseContext& ctx)
{
	TOperator op = EOpNull;
	if (t.matrix) {
		const bool hasNonSquare = (ctx.targetVersion >= ETargetGLSL_120);
		switch(t.matcols) {
			case 2: switch(t.matrows) {
				case 2: op = EOpConstructMat2x2;  break;
				case 3: if (hasNonSquare) op = EOpConstructMat2x3;  break;
				case 4: if (hasNonSquare) op = EOpConstructMat2x4;  break;
			} break;
			case 3: switch(t.matrows) {
				case 2: if (hasNonSquare) op = EOpConstructMat3x2;  break;
				case 3: op = EOpConstructMat3x3;  break;
				case 4: if (hasNonSquare) op = EOpConstructMat3x4;  break;
			} break;
			case 4: switch(t.matrows) {
				case 2: if (hasNonSquare) op = EOpConstructMat4x2;  break;
				case 3: if (hasNonSquare) op = EOpConstructMat4x3;  break;
				case 4: op = EOpConstructMat4x4;  break;
			} break;
		}
	} else {
		switch(t.matrows) {
			case 1: op = EOpConstructFloat; break;
			case 2: op = EOpConstructVec2;  break;
			case 3: op = EOpConstructVec3;  break;
			case 4: op = EOpConstructVec4;  break;
		}
	}
	return op;
}
