gap_story_vthumb_get_velem_no_movie(GapStbMainGlobalParams *sgpp
              ,GapStoryBoard *stb
              ,GapStoryElem *stb_elem
              )
{
  GapStoryVTResurceElem *velem;
  GapStorySection *referenced_section;
  GapStoryVthumbEnum vt_type;
  gint32 section_id;
  gint32 version;
  const char *name;

  if((sgpp == NULL) || (stb_elem == NULL)) { return (NULL); }

  referenced_section = NULL;
  section_id = -1;
  switch(stb_elem->record_type)
  {
     case GAP_STBREC_VID_SECTION:
       vt_type = GAP_STB_VLIST_SECTION;
       name = stb_elem->orig_filename;
       if (name == NULL)
       {


         return(NULL);
       }
       referenced_section =
         gap_story_find_section_by_name(stb, name);

       if (referenced_section == NULL)
       {


         return(NULL);
       }
       version = referenced_section->version;
       section_id = referenced_section->section_id;


       for(velem = sgpp->video_list; velem != NULL; velem = (GapStoryVTResurceElem *)velem->next)
       {
         if((section_id == velem->section_id)
         && (version == velem->version)
         && (velem->vt_type == GAP_STB_VLIST_SECTION))
         {
           return(velem);
         }
       }
       break;
     case GAP_STBREC_VID_ANIMIMAGE:
       vt_type = GAP_STB_VLIST_ANIM_IMAGE;
       name = stb_elem->orig_filename;  ;
       version = gap_file_get_mtime(name);

       for(velem = sgpp->video_list; velem != NULL; velem = (GapStoryVTResurceElem *)velem->next)
       {
         if((strcmp(velem->video_filename, name) == 0)
         && (version == velem->version)
         && (velem->vt_type == GAP_STB_VLIST_ANIM_IMAGE))
         {
           return(velem);
         }
       }
       break;
     default:
       return (NULL);
       break;
  }


  if(!sgpp->auto_vthumb)
  {
    return(NULL);
  }


  velem = p_new_velem(vt_type);
  if(velem == NULL) { return (NULL); }

  velem->version = version;
  velem->video_filename = g_strdup(name);
  velem->section_id = section_id;
  if(stb_elem->record_type == GAP_STBREC_VID_SECTION)
  {
    velem->total_frames = stb_elem->nframes;
    velem->total_frames = gap_story_count_total_frames_in_section(referenced_section);
  }

  velem->next = sgpp->video_list;
  sgpp->video_list = velem;

  return(velem);

}
