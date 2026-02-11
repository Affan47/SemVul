genCodePostorder(Absyn *node, Table *symtab, int r) {
	switch (node->type) {
	case ABSYN_NAMETY:
	case ABSYN_ARRAYTY:
	case ABSYN_TYPEDEC:
	case ABSYN_PARDEC:
	case ABSYN_EMPTYSTM:
	case ABSYN_VARDEC:

        return;	break;

	case ABSYN_PROCDEC:
		genCodePostorderProcDec(node, symtab, r);
        return;	break;
	case ABSYN_COMPSTM:
		genCodePostorderCompStm(node, symtab, r);
        return;	break;
	case ABSYN_ASSIGNSTM:
		genCodePostorderAssignStm(node, symtab, r);
        return;	break;
	case ABSYN_IFSTM:
		genCodePostorderIfStm(node, symtab, r);
        return;	break;
	case ABSYN_WHILESTM:
		genCodePostorderWhileStm(node, symtab, r);
        return;	break;
	case ABSYN_CALLSTM:
		genCodePostorderCallStm(node, symtab, r);
        return;	break;
	case ABSYN_OPEXP:
		genCodePostorderOpExp(node, symtab, r);
        return;	break;
	case ABSYN_VAREXP:
		genCodePostorderVarExp(node, symtab, r);
        return;	break;
	case ABSYN_INTEXP:
		genCodePostorderIntExp(node, symtab, r);
        return;	break;
	case ABSYN_SIMPLEVAR:
		genCodePostorderSimpleVar(node, symtab, r);
        return;	break;
	case ABSYN_ARRAYVAR:
		genCodePostorderArrayVar(node, symtab, r);
        return;	break;
	case ABSYN_DECLIST:
		genCodePostorderDecList(node, symtab, r);
        return;	break;
	case ABSYN_STMLIST:
		genCodePostorderStmList(node, symtab, r);
        return;	break;
	case ABSYN_EXPLIST:
		genCodePostorderExpList(node, symtab, r);
        return;	break;
	default:
		error("unknown node type %d in genCodePostorder, line %d", node->type,
		      node->line);
	}
}
