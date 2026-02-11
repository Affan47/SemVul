getBasis(const unsigned char * statusArray) const
{
  int iRow,iColumn;
  int numberRows = modelPtr_->numberRows();
  int numberColumns = modelPtr_->numberColumns();
  CoinWarmStartBasis * basis = new CoinWarmStartBasis();
  basis->setSize(numberColumns,numberRows);

  int lookupA[]={0,1,3,2,0,2};
  for (iRow=0;iRow<numberRows;iRow++) {
    int iStatus = statusArray[numberColumns+iRow]&7;
    iStatus = lookupA[iStatus];
    basis->setArtifStatus(iRow,static_cast<CoinWarmStartBasis::Status> (iStatus));
  }
  int lookupS[]={0,1,2,3,0,3};
  for (iColumn=0;iColumn<numberColumns;iColumn++) {
    int iStatus = statusArray[iColumn]&7;
    iStatus = lookupS[iStatus];
    basis->setStructStatus(iColumn,static_cast<CoinWarmStartBasis::Status> (iStatus));
  }

  return basis;
}
