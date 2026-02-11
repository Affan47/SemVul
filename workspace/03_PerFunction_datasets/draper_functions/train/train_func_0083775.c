semi_print(data_t *data)
{
    if(!data) {
        OUTPUT_REG("NULL pointer");
        return;
    }

    switch(data->type)
    {
    case DT_PAIR:
        OUTPUT_REG("pair: car=%d(0x%x) cdr=%d(0x%x)",
                   CAR(data), CAR(data),
                   CDR(data), CDR(data));
        break;
    case DT_NUMBER:
        OUTPUT_REG("number: %f", data->data.number);
        break;
    case DT_PROCEDURE:
        OUTPUT_REG("procedure: args=%d(0x%x) code=%d(0x%x) env=%d(0x%x)",
                   data->data.procedure.args,
                   data->data.procedure.args,
                   data->data.procedure.code,
                   data->data.procedure.code,
                   data->data.procedure.env,
                   data->data.procedure.env);
        break;
    case DT_MACRO:
        OUTPUT_REG("macro: args=%d(0x%x) code=%d(0x%x)",
                   data->data.procedure.args,
                   data->data.procedure.args,
                   data->data.procedure.code,
                   data->data.procedure.code);
        break;
    case DT_VARIABLE:
        OUTPUT_REG("variable: %s", util_to_mbs(data->data.text));
        break;
    case DT_SYMBOL:
        OUTPUT_REG("symbol: %s", util_to_mbs(data->data.text));
        break;
    case DT_STRING:
        OUTPUT_REG("string: %s", util_to_mbs(data->data.text));
        break;
    case DT_NIL:
        OUTPUT_REG("NIL");
        break;
    case DT_T:
        OUTPUT_REG("#T");
        break;
    case DT_DATAERROR:
        OUTPUT_REG("error: file = %s:%d, error: %ls\n",
                   get_filename_by_index(data->filename),
                   data->line_num,
                   data->data.text);
        break;
    default:
        OUTPUT_REG("warning: unknown type!!");
        break;
    }
}
