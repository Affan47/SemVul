Int (DBObjRecord *record)

	{
	switch (OprTypeVAR)
		{
		case DBMathOperandConst:
			switch (VarTypeVAR)
				{
				case DBVariableString:	return (DBDefaultMissingIntVal);
				case DBVariableInt:		return (Var.Int);
				case DBVariableFloat:
					return (CMmathEqualValues (Var.Float,DBDefaultMissingFloatVal) ?
							  DBDefaultMissingIntVal : (DBInt) Var.Float);
				}
		case DBMathOperandVar:			return (Var.FldPTR->Int (record));
		case DBMathOperandExpr:
		case DBMathOperandCond:			return (Var.ExpPTR->Int (record));
		default:	break;
		}
	return (DBDefaultMissingIntVal);
	}
