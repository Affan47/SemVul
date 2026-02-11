SCPI_ParamNumber(scpi_t * context, const scpi_choice_def_t * special, scpi_number_t * value, scpi_bool_t mandatory)
{
    scpi_token_t token;
    lex_state_t state;
    scpi_parameter_t param;
    scpi_bool_t result;
    int32_t tag;

    if (!value) {
        SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
        return FALSE;
    }

    result = SCPI_Parameter(context, &param, mandatory);

    if (!result) {
        return result;
    }

    state.buffer = param.ptr;
    state.pos = state.buffer;
    state.len = param.len;

    switch(param.type) {
        case SCPI_TOKEN_DECIMAL_NUMERIC_PROGRAM_DATA:
        case SCPI_TOKEN_HEXNUM:
        case SCPI_TOKEN_OCTNUM:
        case SCPI_TOKEN_BINNUM:
        case SCPI_TOKEN_DECIMAL_NUMERIC_PROGRAM_DATA_WITH_SUFFIX:
        case SCPI_TOKEN_PROGRAM_MNEMONIC:
            value->unit = SCPI_UNIT_NONE;
            value->special = FALSE;
            result = TRUE;
            break;
    }

    switch(param.type) {
        case SCPI_TOKEN_DECIMAL_NUMERIC_PROGRAM_DATA:
        case SCPI_TOKEN_DECIMAL_NUMERIC_PROGRAM_DATA_WITH_SUFFIX:
        case SCPI_TOKEN_PROGRAM_MNEMONIC:
            value->base = 10;
            break;
        case SCPI_TOKEN_BINNUM:
            value->base = 2;
            break;
        case SCPI_TOKEN_HEXNUM:
            value->base = 16;
            break;
        case SCPI_TOKEN_OCTNUM:
            value->base = 8;
            break;
    }

    switch(param.type) {
        case SCPI_TOKEN_DECIMAL_NUMERIC_PROGRAM_DATA:
            SCPI_ParamToDouble(context, &param, &(value->value));
            break;
        case SCPI_TOKEN_HEXNUM:
            SCPI_ParamToDouble(context, &param, &(value->value));
            break;
        case SCPI_TOKEN_OCTNUM:
            SCPI_ParamToDouble(context, &param, &(value->value));
            break;
        case SCPI_TOKEN_BINNUM:
            SCPI_ParamToDouble(context, &param, &(value->value));
            break;
        case SCPI_TOKEN_DECIMAL_NUMERIC_PROGRAM_DATA_WITH_SUFFIX:
            scpiLex_DecimalNumericProgramData(&state, &token);
            scpiLex_WhiteSpace(&state, &token);
            scpiLex_SuffixProgramData(&state, &token);

            SCPI_ParamToDouble(context, &param, &(value->value));

            result = transformNumber(context, token.ptr, token.len, value);
            break;
        case SCPI_TOKEN_PROGRAM_MNEMONIC:
            scpiLex_WhiteSpace(&state, &token);
            scpiLex_CharacterProgramData(&state, &token);


            SCPI_ParamToChoice(context, &token, special, &tag);

            value->special = TRUE;
            value->tag = tag;

            break;
        default:
            result = FALSE;
    }

    return result;
}
