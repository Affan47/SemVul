calculate_mul_if_necessary(Node node, RfmStm stm)
{
    RfmOperand    operand;
    Boolean       is_integer8;
    long long int value1;
    long long int value2;
    long long int value;
    RfmConst      cnst;

    if (node->CODE != NODE_MUL)  {
        return(NULL);
    }
    if ((node->RESULT_ATTR == ATTR1_SIGNED_LONG_LONG) ||
        (node->RESULT_ATTR == ATTR1_UNSIGNED_LONG_LONG)) {
        is_integer8 = TRUE;
    } else {
        is_integer8 = FALSE;
    }
    if ((IsIntegerConst(node->FIRST_CHILD, &value1)) &&
        (IsIntegerConst(node->SECOND_CHILD, &value2))) {
        if (is_integer8 == FALSE) {
            value = value1 * value2;
            if ((value > INT_MAX) ||
                (value < INT_MIN)) {
                return(NULL);
            }
        } else {
            if (CHECK_LLONG_MUL_OVERFLOW(value1, value2)) {
                return(NULL);
            }
            value = value1 * value2;
        }
    } else {
        return(NULL);
    }
    cnst = MakeIntegerRfmConst(value, is_integer8);
    operand = MakeConstRfmOperand(cnst, stm);

    return(operand);
}
