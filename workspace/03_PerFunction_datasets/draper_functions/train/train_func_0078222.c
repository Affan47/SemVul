FcVStackPopAndDestroy (FcConfigParse *parse)
{
    FcVStack	*vstack = parse->vstack;

    if (!vstack || vstack->pstack != parse->pstack)
	return;

    parse->vstack = vstack->prev;

    switch (vstack->tag) {
    case FcVStackNone:
	break;
    case FcVStackName:
	break;
    case FcVStackFamily:
	break;
    case FcVStackString:
    case FcVStackConstant:
    case FcVStackGlob:
	FcStrFree (vstack->u.string);
	break;
    case FcVStackPattern:
	FcPatternDestroy (vstack->u.pattern);
	break;
    case FcVStackInteger:
    case FcVStackDouble:
	break;
    case FcVStackMatrix:
	FcExprMatrixFreeShallow (vstack->u.matrix);
	break;
    case FcVStackRange:
    case FcVStackBool:
	break;
    case FcVStackCharSet:
	FcCharSetDestroy (vstack->u.charset);
	break;
    case FcVStackLangSet:
	FcLangSetDestroy (vstack->u.langset);
	break;
    case FcVStackTest:
	FcTestDestroy (vstack->u.test);
	break;
    case FcVStackExpr:
    case FcVStackPrefer:
    case FcVStackAccept:
    case FcVStackDefault:
	FcExprDestroy (vstack->u.expr);
	break;
    case FcVStackEdit:
	FcEditDestroy (vstack->u.edit);
	break;
    }

    if (vstack == &parse->vstack_static[parse->vstack_static_used - 1])
	parse->vstack_static_used--;
    else
	free (vstack);
}
