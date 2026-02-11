Adjust2Mul(Quadruple *qpt)
{
    const Const_table*  op1;
    const Const_table*  op2;
    int     ret_int = 0;
    real    ret_real = 0.0;
    double  ret_double = 0.0;
    char         ret_char = 0;
    unsigned char ret_uc = 0;
    short        ret_short = 0;
    unsigned short ret_us = 0;
    unsigned int  ret_ui = 0;
    symbol_type  rettype;
    long long    ret_ll = 0;
    unsigned long long ret_ull = 0;

    op1 = qpt->op[1]->tbl.c;
    op2 = qpt->op[2]->tbl.c;
    rettype = get_result_type_of_2op(op1->type, op2->type);
    switch (rettype) {
    case TYPE_INT:
    case TYPE_LONG:
	ret_int = AdjustCDataInt(op1) * AdjustCDataInt(op2);
	break;
    case TYPE_LONGLONG:
	ret_ll = AdjustCDataLongLong(op1) * AdjustCDataLongLong(op2);
	break;
    case TYPE_REAL:
	ret_real = AdjustCDataReal(op1) * AdjustCDataReal(op2);
	break;
    case TYPE_DOUBLE:
    case TYPE_LONG_DOUBLE:
	ret_double = AdjustCDataDouble(op1) * AdjustCDataDouble(op2);
	break;
    case TYPE_CHAR:
	ret_char = AdjustCDataChar(op1) * AdjustCDataChar(op2);
	break;
    case TYPE_UNSIGNED_CHAR:
	ret_uc = AdjustCDataUnsignedChar(op1) * AdjustCDataUnsignedChar(op2);
	break;
    case TYPE_SHORT:
	ret_short = AdjustCDataShort(op1) * AdjustCDataShort(op2);
	break;
    case TYPE_UNSIGNED_SHORT:
	ret_us = AdjustCDataUnsignedShort(op1) * AdjustCDataUnsignedShort(op2);
	break;
    case TYPE_UNSIGNED:
    case TYPE_UNSIGNED_LONG:
	ret_ui = AdjustCDataUnsignedInt(op1) * AdjustCDataUnsignedInt(op2);
	break;
    case TYPE_UNSIGNED_LONGLONG:
	ret_ui = AdjustCDataUnsignedLongLong(op1) *
		 AdjustCDataUnsignedLongLong(op2);
	break;

    default:
	fatal("Unexpected constant type.\n");
    }

    return  GetConstTableOnCorrectType(qpt, rettype,
				       ret_int, ret_real, ret_double,
				       ret_char, ret_uc, ret_short, ret_us,
				       ret_ui, ret_ll, ret_ull);
}
