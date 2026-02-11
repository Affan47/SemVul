shipoutWithCallback(struct FlattenSpec *spec, rgba **pixels,
                    lineCallback callback)
{
  unsigned i ;
  for( i = 0; i < spec->dim.height; i++ ) {
    callback(spec->dim.width,pixels[i]);
  }
  xcffree(pixels);
}
