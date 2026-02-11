scsi_set_speed (cdrom_drive *d, int speed){
  unsigned char cmd[12]={0xBB, 0, 0, 0, 0xff, 0xff, 0, 0, 0, 0, 0, 0};
  unsigned char sense[SG_MAX_SENSE];

  if(speed>=0)
    speed=speed*44100*4/1024;
  else
    speed=-1;
  cmd[2] = (speed >> 8) & 0xFF;
  cmd[3] = (speed) & 0xFF;
  return handle_scsi_cmd(d,cmd,12,0,0,0,0,sense);
}
