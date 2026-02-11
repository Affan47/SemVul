TIFF_Image (const char* filename) {
    GraphicComp* comp = nil;
    Raster* raster = TIFFRaster::load(filename);

    if (raster != nil) {
#ifndef NOREF
        raster->ref();
#endif
        raster->flush();
        comp = new RasterComp(new RasterRect(raster), filename);
    }

    return comp;
}
