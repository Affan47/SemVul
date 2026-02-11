Cbc_getVectorLengths(Cbc_Model * model)
{
    const char prefix[] = "Cbc_C_Interface::Cbc_getVectorLengths(): ";

    if (VERBOSE > 0) printf("%s begin\n", prefix);

    const int * result = NULL;
    const CoinPackedMatrix * matrix = NULL;
    matrix = model->model_->solver()->getMatrixByCol();
    result = (matrix == NULL) ? NULL : matrix->getVectorLengths();

    if (VERBOSE > 0)
        printf("%s return %p\n", prefix, static_cast<const void*>(result));
    return result;
}
