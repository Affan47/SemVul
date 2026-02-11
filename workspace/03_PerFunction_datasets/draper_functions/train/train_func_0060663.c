generic_nvram_extract_config(vm_instance_t *vm, char *dev_name, size_t nvram_offset, size_t nvram_size, m_uint32_t addr, u_int format,
                                 u_char **startup_config, size_t *startup_len, u_char **private_config, size_t *private_len)
{

   u_char *base_ptr;
   struct vdevice *nvram_dev;
   off_t file_size;
   int fd;
   int ret = 0;
   fs_nvram_t *fs = NULL;

   if ((nvram_dev = dev_get_by_name(vm, dev_name)))
      dev_sync(nvram_dev);

   fd = vm_mmap_open_file(vm, dev_name, &base_ptr, &file_size);
   if (fd == -1)
      return(-1);

   if (nvram_size == 0 && file_size >= nvram_offset + FS_NVRAM_SECTOR_SIZE)
      nvram_size = (size_t)file_size - nvram_offset;

   if (file_size < nvram_offset + nvram_size) {
      vm_error(vm,"generic_nvram_extract_config: NVRAM filesystem doesn't fit inside the %s file!\n", dev_name);
      goto done;
   }


   fs = fs_nvram_open(base_ptr + nvram_offset, nvram_size, addr, (format & FS_NVRAM_FORMAT_MASK));
   if (fs == NULL)
      goto err_errno;

   ret = fs_nvram_read_config(fs, startup_config, startup_len, private_config, private_len);
   if (ret)
      goto err_ret;

done:
   if (fs)
      fs_nvram_close(fs);

   vm_mmap_close_file(fd, base_ptr, file_size);

   return(ret);
err_errno:
   ret = errno;
err_ret:
   vm_error(vm,"generic_nvram_extract_config: %s\n", strerror(ret));
   ret = -1;
   goto done;
}
