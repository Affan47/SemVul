php_eval_int_math(PHP_EXP_OP op, PHP_VALUE_NODE *op1, PHP_VALUE_NODE *op2, PHP_VALUE_NODE *result)
{
	cast_value_dnum(op1);
	cast_value_dnum(op2);
	result->type = PHP_VAL_INT;
	switch(op) {
    	case PHP_OP_SHL:
    		result->int_val = op1->int_val << op2->int_val;
    		break;
    	case PHP_OP_SHR:
    		result->int_val = op1->int_val >> op2->int_val;
    		break;
    	case PHP_OP_OR:
    		result->int_val = op1->int_val | op2->int_val;
    		break;
		case PHP_OP_LOG_OR:
    		result->int_val = op1->int_val || op2->int_val;
    		break;
    	case PHP_OP_AND:
    		result->int_val = op1->int_val & op2->int_val;
    		break;
		case PHP_OP_LOG_AND:
    		result->int_val = op1->int_val && op2->int_val;
    		break;
		case PHP_OP_LOG_XOR:
			op1->int_val = op1->int_val ? 1 : 0;
			op2->int_val = op2->int_val ? 1 : 0;
    	case PHP_OP_XOR:
    		result->int_val = op1->int_val ^ op2->int_val;
    		break;
		default:
			php_report_error(PHP_INTERNAL_ERROR, "This op is not int math");
	}
}
