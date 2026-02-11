Equal(MatrixFM* matrix) {
    bool equal = true;

    if ((this->_rowCount != matrix->_rowCount) || (this->_columnCount != matrix->_columnCount)) {
        equal = false;
    }
    else {
        for (int row = 0; row < this->_blockRowCount; ++row) {
            for (int column = 0; column < this->_blockColumnCount; ++column) {
                for (int i = 0; i < BlockSize; ++i) {
                if (std::abs(this->GetValue(row, column) - matrix->GetValue(row, column)) / this->GetValue(row, column)
                        >= MatrixFM::FractionalEquality) {
                        equal = false;
                    }
                }
            }
        }
    }

    return equal;
}
