resolve_reference(CdlExpression expr, int index)
{
    CYG_REPORT_FUNCNAMETYPE("CdlEvalContext::resolve_reference", "result %");
    CYG_REPORT_FUNCARG2XV(expr, index);
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITION_CLASSC(expr);
    CYG_PRECONDITIONC((0 <= index) && (index <= (int)expr->references.size()));


    CdlNode result = 0;
    if (0 != this->property) {

        result = expr->references[index].get_destination();
    } else {


        if (0 != this->toplevel) {
            std::string destination_name = expr->references[index].get_destination_name();
            result = this->toplevel->lookup(destination_name);
        }
    }

    CYG_REPORT_RETVAL(result);
    return result;
}
