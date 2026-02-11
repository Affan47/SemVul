Image_emergency_backup()
{
#ifndef NOLAYERS
  if (Main_backups && Main_backups->Pages && Main_backups->Pages->Nb_layers == 1)
    Emergency_backup(SAFETYBACKUP_PREFIX_A "999999" BACKUP_FILE_EXTENSION,Main_screen, Main_image_width, Main_image_height, &Main_palette);
  if (Spare_backups && Spare_backups->Pages && Spare_backups->Pages->Nb_layers == 1)
    Emergency_backup(SAFETYBACKUP_PREFIX_B "999999" BACKUP_FILE_EXTENSION,Spare_visible_image.Image, Spare_image_width, Spare_image_height, &Spare_palette);
#endif
}
