stsd_dump_subtitle_tx3g(int indent, qt_sample_description_t * d)
  {
  bgav_diprintf(indent, "fourcc:                   ");
  bgav_dump_fourcc(d->fourcc);
  bgav_dprintf( "\n");
  bgav_diprintf(indent, "data_reference_index:     %d\n",
                d->data_reference_index);
  bgav_diprintf(indent, "display_flags:            %08x\n",
                d->format.subtitle_tx3g.display_flags);
  bgav_diprintf(indent, "horizontal_justification: %d\n",
                d->format.subtitle_tx3g.horizontal_justification);
  bgav_diprintf(indent, "vertical_justification:   %d\n",
                d->format.subtitle_tx3g.vertical_justification);
  bgav_diprintf(indent, "back_color:               [%d,%d,%d,%d]\n",
                d->format.subtitle_tx3g.back_color[0],
                d->format.subtitle_tx3g.back_color[1],
                d->format.subtitle_tx3g.back_color[2],
                d->format.subtitle_tx3g.back_color[3]);
  bgav_diprintf(indent, "defaultTextBox:           [%d,%d,%d,%d]\n",
                d->format.subtitle_tx3g.defaultTextBox[0],
                d->format.subtitle_tx3g.defaultTextBox[1],
                d->format.subtitle_tx3g.defaultTextBox[2],
                d->format.subtitle_tx3g.defaultTextBox[3]);
  bgav_diprintf(indent, "start_char_offset:        %d\n",
                d->format.subtitle_tx3g.start_char_offset);
  bgav_diprintf(indent, "end_char_offset:          %d\n",
                d->format.subtitle_tx3g.end_char_offset);
  bgav_diprintf(indent, "font_id:                  %d\n",
                d->format.subtitle_tx3g.font_id);
  bgav_diprintf(indent, "style_flags:              %d\n",
                d->format.subtitle_tx3g.style_flags);
  bgav_diprintf(indent, "font_size:                %d\n",
                d->format.subtitle_tx3g.font_size);
  bgav_diprintf(indent, "text_color:               [%d,%d,%d,%d]\n",
                d->format.subtitle_tx3g.text_color[0],
                d->format.subtitle_tx3g.text_color[1],
                d->format.subtitle_tx3g.text_color[2],
                d->format.subtitle_tx3g.text_color[3]);
  if(d->format.subtitle_tx3g.has_ftab)
    bgav_qt_ftab_dump(indent, &d->format.subtitle_tx3g.ftab);
  }
