ReadVolume(int first, int last,
                                   vtkUnsignedShortArray *scalars)
{
  unsigned short *pixels;
  unsigned short *slice;
  FILE *fp;
  int numPts;
  int fileNumber;
  int status;
  int numberSlices = last - first + 1;
  char filename[1024];
  int dimensions[3];
  int bounds[6];


  numPts = this->DataDimensions[0] * this->DataDimensions[1];


  this->ComputeTransformedDimensions (dimensions);


  this->ComputeTransformedBounds (bounds);


  slice = new unsigned short[numPts];


  pixels = scalars->WritePointer(0, numPts*numberSlices);

  vtkDebugMacro (<< "Creating scalars with " << numPts * numberSlices
                 << " points.");


  for (fileNumber = first; fileNumber <= last; fileNumber++)
    {

    if (this->FilePattern)
      {
      sprintf (filename, this->FilePattern, this->FilePrefix, fileNumber);
      }
    else
      {
      sprintf (filename, this->FilePattern, fileNumber);
      }
    if ( !(fp = fopen(filename,"rb")) )
      {
      vtkErrorMacro(<<"Can't find file: " << filename);
      return;
      }

    vtkDebugMacro ( << "Reading " << filename );


    status = this->Read16BitImage (fp, slice, this->DataDimensions[0],
                    this->DataDimensions[1], this->HeaderSize, this->SwapBytes);

    fclose (fp);

    if (status == 0)
      {
      break;
      }


    this->TransformSlice (slice, pixels, fileNumber - first, dimensions, bounds);
    }

  delete []slice;
}
