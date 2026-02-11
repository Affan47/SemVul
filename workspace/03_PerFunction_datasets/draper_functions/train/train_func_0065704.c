EvaluateGE(IODSCellEvaluator* poEvaluator)
{
    CPLAssert( eNodeType == SNT_OPERATION );
    CPLAssert( eOp == ODS_GE );

    CPLAssert(nSubExprCount == 2);
    if (!(papoSubExpr[0]->Evaluate(poEvaluator)))
        return FALSE;
    if (!(papoSubExpr[1]->Evaluate(poEvaluator)))
        return FALSE;

    CPLAssert(papoSubExpr[0]->eNodeType == SNT_CONSTANT );
    CPLAssert(papoSubExpr[1]->eNodeType == SNT_CONSTANT );

    int bVal = FALSE;
    if (papoSubExpr[0]->field_type == ODS_FIELD_TYPE_INTEGER)
    {
        if (papoSubExpr[1]->field_type == ODS_FIELD_TYPE_INTEGER)
        {
            bVal = (papoSubExpr[0]->int_value >= papoSubExpr[1]->int_value);
        }
        else if (papoSubExpr[1]->field_type == ODS_FIELD_TYPE_FLOAT)
        {
            bVal = (papoSubExpr[0]->int_value >= papoSubExpr[1]->float_value);
        }
    }
    else if (papoSubExpr[0]->field_type == ODS_FIELD_TYPE_FLOAT)
    {
        if (papoSubExpr[1]->field_type == ODS_FIELD_TYPE_INTEGER)
        {
            bVal = (papoSubExpr[0]->float_value >= papoSubExpr[1]->int_value);
        }
        else if (papoSubExpr[1]->field_type == ODS_FIELD_TYPE_FLOAT)
        {
            bVal = (papoSubExpr[0]->float_value >= papoSubExpr[1]->float_value);
        }
    }
    else if (papoSubExpr[0]->field_type == ODS_FIELD_TYPE_STRING)
    {
        if (papoSubExpr[1]->field_type == ODS_FIELD_TYPE_STRING)
        {
            if (GetCase(papoSubExpr[0]->string_value) ==
                GetCase(papoSubExpr[1]->string_value))
                bVal = (strcmp(papoSubExpr[0]->string_value,
                               papoSubExpr[1]->string_value) >= 0);
            else
                bVal = (strcasecmp(papoSubExpr[0]->string_value,
                                   papoSubExpr[1]->string_value) >= 0);
        }
        else
            bVal = TRUE;
    }
    else
    {
        CPLError(CE_Failure, CPLE_NotSupported,
                 "Bad argument type for %s", ODSGetOperatorName(eOp));
        return FALSE;
    }

    eNodeType = SNT_CONSTANT;
    field_type = ODS_FIELD_TYPE_INTEGER;
    int_value = bVal;

    FreeSubExpr();

    return TRUE;
}
