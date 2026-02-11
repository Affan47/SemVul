display_func_helper(data_t *arg)
{
    switch(arg->type) {
    case DT_STRING:
    case DT_SYMBOL:
    case DT_VARIABLE:
    case DT_DATAERROR:
    {
        char tmp[MAX_STRING_LEN];
        wcstombs(tmp, arg->data.text, MAX_STRING_LEN);
        OUTPUT_ERR("%s", tmp);

        if(arg->type == DT_DATAERROR) {
            OUTPUT_ERR(" > error at %s:%d\n",
                       get_filename_by_index(arg->filename),
                       arg->line_num);
        }

        break;
    }
    case DT_PROCEDURE:
        OUTPUT_REG("{compound procedure}%d", (int)arg);
        break;
    case DT_NUMBER:
        OUTPUT_REG("%f", arg->data.number);
        break;
    case DT_PAIR:
        OUTPUT_REG("(");

        while(arg != DataNIL) {
            data_t *car = CAR(arg);
            display_func_helper(car);
            arg = CDR(arg);
            OUTPUT_REG(" ");
        }

        OUTPUT_REG(" )");
        break;
    case DT_NIL:
        OUTPUT_REG("NIL");
        break;
    case DT_T:
        OUTPUT_REG("#T");
        break;
    default:
        OUTPUT_ERR("error in display");
        return DataNIL;
    }

    return DataTrue;
}
