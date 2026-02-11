readVariableColumns (const std::vector<String> &varColumns)
  {
    int   rowsRead=0;
    int   status=0;
    int   sz=varColumns.size();


    int i = 0;
    FITSUtil::auto_array_ptr<long> pBinSizes(new long[rows()]);
    long*  binSizes = pBinSizes.get();
    FITSUtil::auto_array_ptr<long> pOffsets(new long[rows()]);
    long*  offsets  = pOffsets.get();
    while ( i < sz && status == 0 )
    {

       Column& thisColumn = column(varColumns[i]);
       int colnum = thisColumn.index();
       status = fits_read_descripts(fitsPointer(), colnum, 1, rows() , binSizes,
				    offsets, &status);
       if (status != 0) break;

       for (rowsRead=0; rowsRead < rows() ; rowsRead++)
       {
	  if (binSizes[rowsRead] > 0)
	     thisColumn.readData(rowsRead+1, binSizes[rowsRead], 1);
       }
       column(varColumns[i]).isRead(true);
       i++;

    }


    if (status != 0)  throw FitsError(status);
  }
