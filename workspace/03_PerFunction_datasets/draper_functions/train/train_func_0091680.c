writeLp(const char *filename,
                               const char *extension ,
                               double epsilon ,
                               int numberAcross ,
                               int decimals ,
                               double objSense ,
                               bool changeNameOnRange) const
{
  std::string f(filename);
  std::string e(extension);
  std::string fullname;
  if (e!="") {
    fullname = f + "." + e;
  } else {

    fullname = f;
  }

  const char * const * const rowNames = modelPtr_->rowNamesAsChar();
  const char * const * const columnNames = modelPtr_->columnNamesAsChar();

  OsiSolverInterface::writeLpNative(fullname.c_str(),
				    rowNames,columnNames, epsilon, numberAcross,
				    decimals, objSense,changeNameOnRange);
  if (rowNames) {
    modelPtr_->deleteNamesAsChar(rowNames, modelPtr_->numberRows_+1);
    modelPtr_->deleteNamesAsChar(columnNames, modelPtr_->numberColumns_);
  }
}
