Equal(Matrix1D* matrix) {
    bool equal = true;

    if ((this->_rowCount != matrix->_rowCount) || (this->_columnCount != matrix->_columnCount)) {
        equal = false;
    }
    else {
        for (int row = 0; row < this->_rowCount; ++row) {
            for (int column = 0; column < this->_columnCount; ++column) {
                if (std::abs(this->GetValue(row, column) - matrix->GetValue(row, column)) / this->GetValue(row, column)
                        >= Matrix1D::FractionalEquality) {
                    equal = false;
                }
            }
        }
    }

    return equal;
}
