EvaluateCONCAT(IODSCellEvaluator* poEvaluator)
{
    CPLAssert( eNodeType == SNT_OPERATION );
    CPLAssert( eOp == ODS_CONCAT );

    CPLAssert(nSubExprCount == 2);
    if (!(papoSubExpr[0]->Evaluate(poEvaluator)))
        return FALSE;
    if (!(papoSubExpr[1]->Evaluate(poEvaluator)))
        return FALSE;

    CPLAssert(papoSubExpr[0]->eNodeType == SNT_CONSTANT );
    CPLAssert(papoSubExpr[1]->eNodeType == SNT_CONSTANT );

    std::string osLeft(papoSubExpr[0]->TransformToString());
    std::string osRight(papoSubExpr[1]->TransformToString());

    eNodeType = SNT_CONSTANT;
    field_type = ODS_FIELD_TYPE_STRING;
    string_value = CPLStrdup((osLeft + osRight).c_str());

    FreeSubExpr();

    return TRUE;
}
