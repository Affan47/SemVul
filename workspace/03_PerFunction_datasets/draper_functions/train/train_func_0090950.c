Cbc_clone(Cbc_Model * model)
{
    const char prefix[] = "Cbc_C_Interface::Cbc_clone(): ";

    if (VERBOSE > 0) printf("%s begin\n", prefix);

    Cbc_Model * result = new Cbc_Model;
    result->model_     = new CbcModel(*(model->model_));
    result->solver_    = dynamic_cast< OsiClpSolverInterface*> (result->model_->solver());
    result->handler_   = NULL;

    if (VERBOSE > 0) printf("%s return\n", prefix);
    return model;
}
