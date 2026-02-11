EvaluateSingleArgOp(IODSCellEvaluator* poEvaluator)
{
    CPLAssert( eNodeType == SNT_OPERATION );

    const SingleOpStruct* psSingleOp = ODSGetSingleOpEntry(eOp);
    CPLAssert(psSingleOp);

    CPLAssert(nSubExprCount == 1);
    if (!(papoSubExpr[0]->Evaluate(poEvaluator)))
        return FALSE;

    CPLAssert(papoSubExpr[0]->eNodeType == SNT_CONSTANT );
    double dfVal = 0;

    if (papoSubExpr[0]->field_type == ODS_FIELD_TYPE_INTEGER)
    {
        dfVal = psSingleOp->pfnEval(papoSubExpr[0]->int_value);
    }
    else if (papoSubExpr[0]->field_type == ODS_FIELD_TYPE_FLOAT)
    {
        dfVal = psSingleOp->pfnEval(papoSubExpr[0]->float_value);
    }
    else
    {
        CPLError(CE_Failure, CPLE_NotSupported, "Bad argument type for %s",
                 psSingleOp->pszName);
        return FALSE;
    }

    eNodeType = SNT_CONSTANT;
    field_type = ODS_FIELD_TYPE_FLOAT;
    float_value = dfVal;

    FreeSubExpr();

    return TRUE;
}
