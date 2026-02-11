setInputSolution(const double * solution, double objValue)
{
    delete [] inputSolution_;
    inputSolution_ = NULL;
    if (model_ && solution) {
        int numberColumns = model_->getNumCols();
        inputSolution_ = new double [numberColumns+1];
        memcpy(inputSolution_, solution, numberColumns*sizeof(double));
        inputSolution_[numberColumns] = objValue;
    }
}
