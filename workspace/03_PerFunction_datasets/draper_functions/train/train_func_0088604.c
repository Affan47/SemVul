jl_generate_fptr(jl_function_t *f)
{

    jl_lambda_info_t *li = f->linfo;
    assert(li->functionObject);
    Function *llvmf = (Function*)li->functionObject;
    if (li->fptr == NULL) {
        JL_SIGATOMIC_BEGIN();
        li->fptr = (jl_fptr_t)jl_ExecutionEngine->getPointerToFunction(llvmf);
        JL_SIGATOMIC_END();
    }
    assert(li->fptr != NULL);
    f->fptr = li->fptr;
    llvmf->deleteBody();
}
