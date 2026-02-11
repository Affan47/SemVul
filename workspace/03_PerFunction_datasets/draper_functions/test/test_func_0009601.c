det_berkowitz(const DenseMatrix &A)
{
    std::vector<DenseMatrix> polys;

    berkowitz(A, polys);
    DenseMatrix poly = polys[polys.size() - 1];

    if (polys.size() % 2 == 1)
        return mul(minus_one, poly.get(poly.nrows() - 1, 0));

    return poly.get(poly.nrows() - 1, 0);
}
