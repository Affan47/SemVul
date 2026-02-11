gap_story_att_fw_properties_dialog (GapStbFrameWidget *fw)
{
  GapStbTabWidgets *tabw;

  if(fw == NULL) { return; }
  if(fw->stb_elem_refptr == NULL)  { return; }


  if (fw->stb_elem_refptr->record_type == GAP_STBREC_ATT_TRANSITION)
  {
    tabw = (GapStbTabWidgets *)fw->tabw;
    if(tabw == NULL)  { return; }

    gap_story_att_stb_elem_properties_dialog(tabw, fw->stb_elem_refptr, fw->stb_refptr);
  }
}
