accepts(void *data)
{
    bool pass = true;
    int32_t act_value = _column->getValue(data, _query);
    int32_t ref_value = convertRefValue();
    switch (_opid) {
        case OP_EQUAL:
            pass = act_value == ref_value; break;
        case OP_GREATER:
            pass = act_value > ref_value; break;
        case OP_LESS:
            pass = act_value < ref_value; break;
        default:
            logger(LG_INFO, "Sorry. Operator %s for integers not implemented.", op_names_plus_8[_opid]);
            break;
    }
    return pass != _negate;
}
