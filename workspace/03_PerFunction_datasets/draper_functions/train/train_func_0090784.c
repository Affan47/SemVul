ReadTiles(void* buffer)
{
  if ( this->GetInternalImage()->Compression == COMPRESSION_OJPEG )
    {
    vtkErrorMacro("This reader cannot read old JPEG compression");
    return;
    }

  unsigned char* volume = reinterpret_cast<unsigned char*>(buffer);

  for(unsigned int col = 0;col<this->GetInternalImage()->Width;col+=this->GetInternalImage()->TileWidth)
    {
    for(unsigned int row = 0;row<this->GetInternalImage()->Height;row+=this->GetInternalImage()->TileHeight)
      {
      unsigned char *tempImage;
      tempImage = new unsigned char[ this->GetInternalImage()->TileWidth * this->GetInternalImage()->TileHeight * this->GetInternalImage()->SamplesPerPixel];

      if(TIFFReadTile(this->GetInternalImage()->Image,tempImage, col,row,0,0)<0)
        {
        vtkErrorMacro( << "Cannot read tile : "<< row << "," << col << " from file" );
        if ( tempImage != buffer )
          {
          delete [] tempImage;
          }

        return;
        }

      unsigned int xx, yy;
      for ( yy = 0; yy < this->GetInternalImage()->TileHeight; yy++ )
        {
        for ( xx = 0; xx <  this->GetInternalImage()->TileWidth; xx++ )
          {
          for(unsigned int i=0;i< this->GetInternalImage()->SamplesPerPixel;i++)
            {
            *volume = *(tempImage++);
            volume++;
            }
          }
        }
      }
    }
}
