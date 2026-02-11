create_raster( u_long w, u_long h ) {
  OverlayRaster* raster;
  if (RasterOvComp::UseGrayRaster()) {
    if (maxval() <= 255)
      raster = new GrayRaster(w, h);
    else if (maxval() <= 655335)
      raster = new GrayRaster(w, h, AttributeValue::UShortType);
    else
      raster = new GrayRaster(w, h, AttributeValue::FloatType);
  }
  else {
    raster = new OverlayRaster(w, h);
    raster->gray_flag(true);
  }
  return raster;
}
