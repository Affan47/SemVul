bgav_qt_tkhd_dump(int indent, qt_tkhd_t * c)
  {
  int i, j;
  bgav_diprintf(indent, "tkhd:\n");
  bgav_diprintf(indent+2, "Version:           %d\n", c->version);
  bgav_diprintf(indent+2, "Flags:             %d\n", c->flags);
  bgav_diprintf(indent+2, "Creation time:     %" PRId64 "\n", c->creation_time);
  bgav_diprintf(indent+2, "Modificatiom time: %" PRId64 "\n", c->modification_time);
  bgav_diprintf(indent+2, "Track ID:          %d\n", c->track_id);
  bgav_diprintf(indent+2, "Duration:          %" PRId64 "\n", c->duration);
  bgav_diprintf(indent+2, "Layer:             %d\n", c->layer);
  bgav_diprintf(indent+2, "Alternate Group:   %d\n", c->alternate_group);
  bgav_diprintf(indent+2, "Volume:            %f\n", c->volume);
  bgav_diprintf(indent+2, "Matrix:\n");
  for(i = 0; i < 3; i++)
    {
    bgav_diprintf(indent+2, "  ");
    for(j = 0; j < 3; j++)
      bgav_dprintf( "%f ", c->matrix[3*i+j]);
    bgav_dprintf( "\n");
    }
  bgav_diprintf(indent+2, "Track width:       %f\n", c->track_width);
  bgav_diprintf(indent+2, "Track height:      %f\n", c->track_height);
  }
