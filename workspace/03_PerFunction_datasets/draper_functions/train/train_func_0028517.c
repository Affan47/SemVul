WriteRaster_internal( GDALRasterBandShadow *obj,
                             int xoff, int yoff, int xsize, int ysize,
                             int buf_xsize, int buf_ysize,
                             GDALDataType buf_type,
                             GIntBig buf_size, char *buffer,
                             int pixel_space, int line_space)
{
    GIntBig min_buffer_size = ComputeBandRasterIOSize (buf_xsize, buf_ysize, GDALGetDataTypeSize( buf_type ) / 8,
                                                   pixel_space, line_space, FALSE );
    if ( min_buffer_size == 0 )
      return CE_Failure;

    if ( buf_size < min_buffer_size ) {
      CPLError(CE_Failure, CPLE_AppDefined, "Buffer too small");
      return CE_Failure;
    }

    return GDALRasterIO( obj, GF_Write, xoff, yoff, xsize, ysize,
		        (void *) buffer, buf_xsize, buf_ysize, buf_type, pixel_space, line_space );
}
