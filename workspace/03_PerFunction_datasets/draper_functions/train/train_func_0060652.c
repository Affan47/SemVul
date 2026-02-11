format(const char *vol) {
   const char *fsType, *dev;
   volume_t *volume;
   int result;


   volume = volume_list_lookup_by_mount_point(&volumes, vol);

   if (volume != NULL) {

      result = volume_list_check_mounted(&volumes);
      if (result == 0) {

         if (volume_get_mounted(volume)) {
            result = EBUSY;
         }
         else {

            fsType = volume_get_fs_type(volume);
         }
      }
   }
   else result = ENOENT;


   if (result == 0) {
      dev = volume_get_spec(volume);
      result = ENOSYS;
      if (strcmp(fsType, "ext2") == 0) result = format_ext2(dev);
      else if (strcmp(fsType, "ext3") == 0) result = format_ext3(dev);
      else if (strcmp(fsType, "ext4") == 0) result = format_ext4(dev);
      else if (strcmp(fsType, "vfat") == 0) result = format_vfat(dev);
   }

   return result;
}
