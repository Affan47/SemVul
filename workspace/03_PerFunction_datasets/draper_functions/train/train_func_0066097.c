print(FILE *out) const
{
    assert(OK());

    fprintf(out, "Error {\n") ;

    fprintf(out, "    code = %d;\n", static_cast<int>(_error_code)) ;


    if (*_error_message.begin() == '"' && *(_error_message.end() - 1) == '"')
        fprintf(out, "    message = %s;\n", _error_message.c_str()) ;
    else
        fprintf(out, "    message = \"%s\";\n", _error_message.c_str()) ;

    fprintf(out, "};\n") ;
}
