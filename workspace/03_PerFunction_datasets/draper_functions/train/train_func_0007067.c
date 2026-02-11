sanei_hp_is_active_xpa (HpScsi scsi)
{HpDeviceInfo *info;
 int model_num;

 info = sanei_hp_device_info_get ( sanei_hp_scsi_devicename  (scsi) );
 if (info->active_xpa < 0)
 {
   model_num = sanei_hp_get_max_model (scsi);
   info->active_xpa = (model_num >= 17);
   DBG(5,"sanei_hp_is_active_xpa: model=%d, active_xpa=%d\n",
       model_num, info->active_xpa);
 }
 return info->active_xpa;
}
