vl_scalespace_put_image (VlScaleSpace *self, float const *image)
{
  vl_index o ;
  _vl_scalespace_start_octave_from_image(self, image, self->geom.firstOctave) ;
  _vl_scalespace_fill_octave(self, self->geom.firstOctave) ;
  for (o = self->geom.firstOctave + 1 ; o <= self->geom.lastOctave ; ++o) {
    _vl_scalespace_start_octave_from_previous_octave(self, o) ;
    _vl_scalespace_fill_octave(self, o) ;
  }
}
