atom_trak_set_video_type (AtomTRAK * trak, AtomsContext * context,
    VisualSampleEntry * entry, guint32 scale, GList * ext_atoms_list)
{
  SampleTableEntryMP4V *ste;
  gint dwidth, dheight;
  gint par_n = 0, par_d = 0;

  if ((entry->par_n != 1 || entry->par_d != 1) &&
      (entry->par_n != entry->par_d)) {
    par_n = entry->par_n;
    par_d = entry->par_d;
  }

  dwidth = entry->width;
  dheight = entry->height;


  if (par_n && (context->flavor != ATOMS_TREE_FLAVOR_MOV)) {
    if (par_n > par_d) {
      dwidth = entry->width * par_n / par_d;
      dheight = entry->height;
    } else {
      dwidth = entry->width * par_n / par_d;
      dheight = entry->height;
    }
  }

  atom_trak_set_video_commons (trak, context, scale, dwidth, dheight);
  atom_stsd_remove_entries (&trak->mdia.minf.stbl.stsd);
  ste = atom_trak_add_video_entry (trak, context, entry->fourcc);

  trak->is_video = TRUE;
  trak->is_h264 = (entry->fourcc == FOURCC_avc1);

  ste->version = entry->version;
  ste->width = entry->width;
  ste->height = entry->height;
  ste->depth = entry->depth;
  ste->color_table_id = entry->color_table_id;
  ste->frame_count = entry->frame_count;

  if (ext_atoms_list)
    ste->extension_atoms = g_list_concat (ste->extension_atoms, ext_atoms_list);


  if (par_n && (context->flavor == ATOMS_TREE_FLAVOR_MOV)) {
    ste->extension_atoms = g_list_append (ste->extension_atoms,
        build_pasp_extension (trak, par_n, par_d));
  }
}
