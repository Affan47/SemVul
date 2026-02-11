main()
  {
    FileParser P(Stdin);

    PolynomialSet g=P.parsePolynomialSetWithRing();

    int n=g.getRing().getNumberOfVariables();
    IntegerVectorList l=exponentDifferences(g);

    FieldMatrix L=integerMatrixToFieldMatrix(rowsToIntegerMatrix(l,n),Q);
    L.reduce(false,true);
    L.removeZeroRows();
    pout<<fieldMatrixToIntegerMatrix(L).getRows();

    return 0;
  }
}
