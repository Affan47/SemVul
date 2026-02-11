dvb_base_bin_reset_pmtlist (DvbBaseBin * dvbbasebin)
{
  CamConditionalAccessPmtFlag flag;
  GList *walk;
  GstMpegTsPMT *pmt;

  walk = dvbbasebin->pmtlist;
  while (walk) {
    if (walk->prev == NULL) {
      if (walk->next == NULL)
        flag = CAM_CONDITIONAL_ACCESS_PMT_FLAG_ONLY;
      else
        flag = CAM_CONDITIONAL_ACCESS_PMT_FLAG_FIRST;
    } else {
      if (walk->next == NULL)
        flag = CAM_CONDITIONAL_ACCESS_PMT_FLAG_LAST;
      else
        flag = CAM_CONDITIONAL_ACCESS_PMT_FLAG_MORE;
    }

    pmt = (GstMpegTsPMT *) walk->data;
    cam_device_set_pmt (dvbbasebin->hwcam, pmt, flag);

    walk = walk->next;
  }

  dvbbasebin->pmtlist_changed = FALSE;
}
