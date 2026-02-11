replaceMatrix( ClpMatrixBase * matrix, bool deleteCurrent)
{
     if (deleteCurrent)
          delete matrix_;
     matrix_ = matrix;
     whatsChanged_ = 0;
}
