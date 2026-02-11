ReadCellsBufferAsASCII(std::ifstream & inputFile, void *buffer)
{
  std::string   line;
  SizeValueType index = 0;
  unsigned int  numPoints;

  MetaDataDictionary & metaDic = this->GetMetaDataDictionary();
  unsigned int *       data = static_cast< unsigned int * >( buffer );

  while ( !inputFile.eof() )
    {
    std::getline(inputFile, line, '\n');
    if ( line.find("VERTICES") != std::string::npos )
      {
      unsigned int numberOfVertices = 0;
      ExposeMetaData< unsigned int >(metaDic, "numberOfVertices", numberOfVertices);

      for ( unsigned int ii = 0; ii < numberOfVertices; ii++ )
        {
        inputFile >> numPoints;
        data[index++] = MeshIOBase::VERTEX_CELL;
        data[index++] = numPoints;
        for ( unsigned int jj = 0; jj < numPoints; jj++ )
          {
          inputFile >> data[index++];
          }
        }
      }
    else if ( line.find("LINES") != std::string::npos )
      {
      unsigned int numberOfLines = 0;
      ExposeMetaData< unsigned int >(metaDic, "numberOfLines", numberOfLines);

      for ( unsigned int ii = 0; ii < numberOfLines; ii++ )
        {
        inputFile >> numPoints;
        data[index++] = MeshIOBase::LINE_CELL;
        data[index++] = numPoints;
        for ( unsigned int jj = 0; jj < numPoints; jj++ )
          {
          inputFile >> data[index++];
          }
        }
      }
    else if ( line.find("POLYGONS") != std::string::npos )
      {
      unsigned int numberOfPolygons = 0;
      ExposeMetaData< unsigned int >(metaDic, "numberOfPolygons", numberOfPolygons);

      for ( unsigned int ii = 0; ii < numberOfPolygons; ii++ )
        {
        inputFile >> numPoints;

        data[index++] = MeshIOBase::POLYGON_CELL;
        data[index++] = numPoints;
        for ( unsigned int jj = 0; jj < numPoints; jj++ )
          {
          inputFile >> data[index++];
          }
        }
      }
    }
}
