ReadMeshInformation()
{

  std::ifstream inputFile;


  inputFile.open(this->m_FileName.c_str(), std::ios::in | std::ios::binary);

  if ( !inputFile.is_open() )
    {
    itkExceptionMacro(<< "Unable to open input file " << this->m_FileName);
    }


  unsigned int numberOfParts = 0;
  unsigned int numberOfConnectivityEntries = 0;


  inputFile >> numberOfParts;
  inputFile >> this->m_NumberOfPoints;
  inputFile >> this->m_NumberOfCells;
  inputFile >> numberOfConnectivityEntries;


  if ( m_PartId > numberOfParts )
    {
    for ( unsigned int ii = 0; ii < numberOfParts; ii++ )
      {
      inputFile >> m_FirstCellId >> m_LastCellId;
      }

    m_FirstCellId = 1;
    m_LastCellId = this->m_NumberOfCells;
    }
  else
    {
    unsigned int firstId;
    unsigned int lastId;
    for ( unsigned int ii = 0; ii < m_PartId; ii++ )
      {
      inputFile >> firstId >> lastId;
      }

    inputFile >> m_FirstCellId;
    inputFile >> m_LastCellId;

    for ( unsigned int ii = m_PartId + 1; ii < numberOfParts; ii++ )
      {
      inputFile >> firstId >> lastId;
      }
    }


  m_FilePosition = inputFile.tellg();


  this->m_PointDimension = 3;
  this->m_FileType = ASCII;


  if ( this->m_NumberOfPoints )
    {
    this->m_UpdatePoints = true;
    }


  if ( this->m_NumberOfCells )
    {
    this->m_UpdateCells = true;
    }


  this->m_PointComponentType = DOUBLE;


  double x;
  for ( SizeValueType ii = 0; ii < this->m_NumberOfPoints; ii++ )
    {
    for ( unsigned int jj = 0; jj < this->m_PointDimension; jj++ )
      {
      inputFile >> x;
      }
    }


  int ptId;
  this->m_CellBufferSize = 0;
  SizeValueType numLines = 0;
  while ( numLines < this->m_NumberOfCells )
    {
    inputFile >> ptId;

    this->m_CellBufferSize++;
    if ( ptId < 0 )
      {
      numLines++;
      }
    }


  this->m_CellComponentType  = UINT;
  this->m_CellBufferSize += this->m_NumberOfCells * 2;


  this->m_PointPixelComponentType = FLOAT;
  this->m_PointPixelType = SCALAR;
  this->m_NumberOfPointPixelComponents = itk::NumericTraits< unsigned int >::OneValue();


  this->m_CellPixelComponentType = FLOAT;
  this->m_CellPixelType  = SCALAR;
  this->m_NumberOfCellPixelComponents = itk::NumericTraits< unsigned int >::OneValue();

  inputFile.close();
}
