compute_call_evaluators_nolock(computed_attr_context *c,slapi_compute_output_t outfn,char *type,Slapi_Entry *e)
{
        int rc = -1;
        compute_evaluator *current = NULL;

        for (current = compute_evaluators; (current != NULL) && (-1 == rc); current = current->next) {
                rc = (*(current->function))(c,type,e,outfn);
        }
        return rc;
}
