PPM_Image (istream& in, boolean ascii) {
    GraphicComp* comp = nil;
    int width, height;
    OverlayRaster* raster = PPM_Raster(in, ascii);
    if (raster) {
      comp = new RasterOvComp(new OverlayRasterRect(raster));
    }
    return comp;
}
