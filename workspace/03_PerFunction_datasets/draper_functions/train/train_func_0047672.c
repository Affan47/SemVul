SWQAutoPromoteStringToDateTime( swq_expr_node *poNode )

{
    if( poNode->nSubExprCount < 2 )
        return;

    swq_field_type eArgType = poNode->papoSubExpr[0]->field_type;
    int i;


    for( i = 1; i < poNode->nSubExprCount; i++ )
    {
        swq_expr_node *poSubNode = poNode->papoSubExpr[i];

        if( eArgType == SWQ_STRING
            && (poSubNode->field_type == SWQ_DATE
                || poSubNode->field_type == SWQ_TIME
                || poSubNode->field_type == SWQ_TIMESTAMP) )
            eArgType = SWQ_TIMESTAMP;
    }

    for( i = 0; i < poNode->nSubExprCount; i++ )
    {
        swq_expr_node *poSubNode = poNode->papoSubExpr[i];

        if( eArgType == SWQ_TIMESTAMP
            && (poSubNode->field_type == SWQ_STRING
                || poSubNode->field_type == SWQ_DATE
                || poSubNode->field_type == SWQ_TIME) )
        {
            if( poSubNode->eNodeType == SNT_CONSTANT )
            {
                poSubNode->field_type = SWQ_TIMESTAMP;
            }
        }
    }
}
