parse(std::string data)
{
    CYG_REPORT_FUNCNAMETYPE("CdlGoalExpression::parse", "result %p");

    CdlGoalExpression result = new CdlGoalExpressionBody;

    try {
        int       index         = 0;
        CdlExprOp op            = CdlExprOp_Invalid;
        int       end_index     = 0;


        CdlExpressionBody::continue_parse(result, data, index, op, end_index);


        while (CdlExprOp_EOD != op) {
            op = CdlExprOp_And;
            CdlExpressionBody::continue_parse(result, data, index, op, end_index);
        }
    }
    catch(...) {
        delete result;
        throw;
    }


    result->expression_string = data;
    CYG_REPORT_RETVAL(result);
    return result;
}
