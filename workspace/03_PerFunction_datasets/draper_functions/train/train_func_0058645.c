subexpr_value(CdlTransaction transaction, CdlExpression expr, unsigned int index, CdlSimpleValue& goal, int level)
{
    CYG_REPORT_FUNCNAMETYPE("CdlInfer::subexpr_value", "result %d");
    CYG_REPORT_FUNCARG4XV(transaction, expr, index, level);
    CYG_PRECONDITION_CLASSC(transaction);
    CYG_PRECONDITION_CLASSC(expr);
    CYG_PRECONDITIONC((0 <= index) && (index < expr->sub_expressions.size()));

    bool result = false;
    CdlSubexpression& subexpr = expr->sub_expressions[index];

    switch(subexpr.op) {

      case CdlExprOp_Reference          :


          {
              CdlNode node = expr->references[subexpr.reference_index].get_destination();
              CdlValuable valuable = 0;
              if (0 != node) {
                  valuable = dynamic_cast<CdlValuable>(node);
              }
              result = infer_handle_reference_value(transaction, valuable, goal, level);
              break;
          }

      case CdlExprOp_StringConstant     :
          result = infer_handle_string_constant_value(subexpr.constants, goal);
          break;

      case CdlExprOp_IntegerConstant    :
          result = infer_handle_integer_constant_value(subexpr.constants, goal);
          break;

      case CdlExprOp_DoubleConstant     :
          result = infer_handle_double_constant_value(subexpr.constants, goal);
          break;

      case CdlExprOp_LogicalNot         :
      case CdlExprOp_And                :
      case CdlExprOp_Or                 :
      case CdlExprOp_Implies            :
      case CdlExprOp_Xor                :
      case CdlExprOp_Eqv                :
      {
          bool  new_goal = true;
          if (("0" == goal.get_value()) || ("" == goal.get_value())) {
              new_goal = false;
          }
          result = CdlInfer::subexpr_bool(transaction, expr, index, new_goal, level);
          break;
      }

      case CdlExprOp_Function :
          result = CdlFunction::infer_value(transaction, expr, index, goal, level);
          break;

      default:

          break;
    }

    CYG_REPORT_RETVAL(result);
    return result;
}
