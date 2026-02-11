streamTo(SourceStream& s) const
{
    const char* opStr;
    switch (oper) {
    case OpMult:
	opStr = " * ";
	break;
    case OpDiv:
	opStr = " / ";
	break;
    case OpMod:
	opStr = " % ";
	break;
    case OpPlus:
	opStr = " + ";
	break;
    case OpMinus:
	opStr = " - ";
	break;
    case OpLShift:
	opStr = " << ";
	break;
    case OpRShift:
	opStr = " >> ";
	break;
    case OpURShift:
	opStr = " >>> ";
	break;
    case OpLess:
	opStr = " < ";
	break;
    case OpGreaterEq:
	opStr = " >= ";
	break;
    case OpGreater:
	opStr = " > ";
	break;
    case OpLessEq:
	opStr = " <= ";
	break;
    case OpIn:
	opStr = " in ";
	break;
    case OpInstanceOf:
	opStr = " instanceof ";
	break;
    case OpEqEq:
	opStr = " == ";
	break;
    case OpNotEq:
	opStr = " != ";
	break;
    case OpStrEq:
	opStr = " === ";
	break;
    case OpStrNEq:
	opStr = " !== ";
	break;
    case OpBitAnd:
	opStr = " & ";
	break;
    case OpBitXOr:
	opStr = " ^ ";
	break;
    case OpBitOr:
	opStr = " | ";
	break;
    default:
	assert(!"Unhandled case in BinaryOperatorNode::streamTo()");
	opStr = " ??? ";
	break;
    }
    s.append(expr1, opStr, expr2);
}
