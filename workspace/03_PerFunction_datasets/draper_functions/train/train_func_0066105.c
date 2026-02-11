cmsStageAllocMatrix(cmsContext ContextID, cmsUInt32Number Rows, cmsUInt32Number Cols,
                                     const cmsFloat64Number* Matrix, const cmsFloat64Number* Offset)
{
    cmsUInt32Number i, n;
    _cmsStageMatrixData* NewElem;
    cmsStage* NewMPE;

    n = Rows * Cols;


    if (n == 0) return NULL;
    if (n >= UINT_MAX / Cols) return NULL;
    if (n >= UINT_MAX / Rows) return NULL;
    if (n < Rows || n < Cols) return NULL;

    NewMPE = _cmsStageAllocPlaceholder(ContextID, cmsSigMatrixElemType, Cols, Rows,
                                     EvaluateMatrix, MatrixElemDup, MatrixElemTypeFree, NULL );
    if (NewMPE == NULL) return NULL;


    NewElem = (_cmsStageMatrixData*) _cmsMallocZero(ContextID, sizeof(_cmsStageMatrixData));
    if (NewElem == NULL) return NULL;


    NewElem ->Double = (cmsFloat64Number*) _cmsCalloc(ContextID, n, sizeof(cmsFloat64Number));

    if (NewElem->Double == NULL) {
        MatrixElemTypeFree(NewMPE);
        return NULL;
    }

    for (i=0; i < n; i++) {
        NewElem ->Double[i] = Matrix[i];
    }


    if (Offset != NULL) {

        NewElem ->Offset = (cmsFloat64Number*) _cmsCalloc(ContextID, Cols, sizeof(cmsFloat64Number));
        if (NewElem->Offset == NULL) {
           MatrixElemTypeFree(NewMPE);
           return NULL;
        }

        for (i=0; i < Cols; i++) {
                NewElem ->Offset[i] = Offset[i];
        }

    }

    NewMPE ->Data  = (void*) NewElem;
    return NewMPE;
}
