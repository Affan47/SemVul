GDALRasterBandShadow_WriteRaster__SWIG_0(GDALRasterBandShadow *self,int xoff,int yoff,int xsize,int ysize,int buf_xsize,int buf_ysize,GDALDataType buf_type,char *regularArrayIn,long nRegularArraySizeIn,int nPixelSpace=0,int nLineSpace=0){
    if ((GDT_Byte == GDT_Int16 && buf_type != GDT_Int16 && buf_type != GDT_UInt16 && buf_type != GDT_CInt16) ||
        (GDT_Byte == GDT_Int32 && buf_type != GDT_Int32 && buf_type != GDT_UInt32 && buf_type != GDT_CInt32) ||
        (GDT_Byte == GDT_Float32 && buf_type != GDT_Float32 && buf_type != GDT_CFloat32) ||
        (GDT_Byte == GDT_Float64 && buf_type != GDT_Float64 && buf_type != GDT_CFloat64))
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                "Java array type is not compatible with GDAL data type");
        return CE_Failure;
    }

    GIntBig nMinBufferSizeInBytes = ComputeBandRasterIOSize (
                            buf_xsize, buf_ysize, GDALGetDataTypeSize(buf_type) / 8,
                            nPixelSpace, nLineSpace, sizeof(char) > 1 );
    if (nMinBufferSizeInBytes > 0x7fffffff)
    {
       CPLError(CE_Failure, CPLE_IllegalArg, "Integer overflow");
       nMinBufferSizeInBytes = 0;
    }
    if (nMinBufferSizeInBytes == 0)
        return CE_Failure;
    if (nRegularArraySizeIn < nMinBufferSizeInBytes)
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                "Buffer is too small");
        return CE_Failure;
    }

    return GDALRasterIO( self, GF_Write, xoff, yoff, xsize, ysize,
                                    regularArrayIn, buf_xsize, buf_ysize,
                                    buf_type, nPixelSpace, nLineSpace );
  }
