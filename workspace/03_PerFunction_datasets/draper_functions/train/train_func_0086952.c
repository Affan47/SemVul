p_tabw_add_section_elem (GapStbTabWidgets *tabw, GapStbMainGlobalParams *sgpp, GapStoryBoard *stb_dst)
{
  GapStoryElem *stb_elem;
  GapStorySection *referable_section;
  gint32 l_nframes;

  if(gap_debug) printf("p_tabw_add_section_elem\n");

  if(sgpp == NULL)    { return; }
  if(tabw == NULL)    { return; }
  if(stb_dst == NULL) { return; }
  if(stb_dst->active_section == NULL) { return; }

  referable_section = gap_story_find_first_referable_subsection(stb_dst);
  if(referable_section == NULL) { return; }

  l_nframes = gap_story_count_total_frames_in_section(referable_section);

  stb_elem = gap_story_new_elem(GAP_STBREC_VID_SECTION);
  stb_elem->orig_filename = g_strdup(referable_section->section_name);
  stb_elem->track = tabw->vtrack;
  stb_elem->from_frame = 1;
  stb_elem->to_frame = l_nframes;
  stb_elem->nloop = 1;
  stb_elem->nframes = l_nframes;
  if(stb_elem)
  {
    gap_stb_undo_group_begin(tabw);
    gap_stb_undo_push(tabw, GAP_STB_FEATURE_CREATE_SECTION_CLIP);

    gap_story_list_append_elem(stb_dst, stb_elem);


    p_recreate_tab_widgets( stb_dst
                                 ,tabw
                                 ,tabw->mount_col
                                 ,tabw->mount_row
                                 ,sgpp
                                 );
    p_render_all_frame_widgets(tabw);
    gap_story_stb_elem_properties_dialog(tabw, stb_elem, stb_dst);
    gap_stb_undo_group_end(tabw);
  }

  p_tabw_update_frame_label_and_rowpage_limits(tabw, sgpp);
}
