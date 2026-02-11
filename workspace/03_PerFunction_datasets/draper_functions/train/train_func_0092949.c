eq(const MatrixBase &other) const
{
	if (this->nrows() != other.nrows() || this->ncols() != other.ncols())
        return false;

    for (unsigned i = 0; i < this->nrows(); i++)
        for (unsigned j = 0; j < this->ncols(); j++)
        if(neq(this->get(i, j), other.get(i, j)))
            return false;

    return true;
}
