dev_remove(vm_instance_t *vm,struct vdevice *dev)
{
   if (dev == NULL)
      return;

   vm_unbind_device(vm,dev);

   vm_log(vm,"DEVICE",
          "Removal of device %s, fd=%d, host_addr=0x%llx, flags=%d\n",
          dev->name,dev->fd,(m_uint64_t)dev->host_addr,dev->flags);

   if (dev->flags & VDEVICE_FLAG_REMAP) {
      dev_init(dev);
      return;
   }

   if (dev->flags & VDEVICE_FLAG_SPARSE) {
      dev_sparse_shutdown(dev);

      if (dev->flags & VDEVICE_FLAG_GHOST) {
         vm_ghost_image_release(dev->fd);
         dev_init(dev);
         return;
      }
   }

   if (dev->fd != -1) {

      if (dev->host_addr) {
         if (dev->flags & VDEVICE_FLAG_SYNC) {
            memzone_sync_all((void *)dev->host_addr,dev->phys_len);
         }

         vm_log(vm,"MMAP","unmapping of device '%s', "
                "fd=%d, host_addr=0x%llx, len=0x%x\n",
                dev->name,dev->fd,(m_uint64_t)dev->host_addr,dev->phys_len);
         memzone_unmap((void *)dev->host_addr,dev->phys_len);
      }

      if (dev->flags & VDEVICE_FLAG_SYNC)
         fsync(dev->fd);

      close(dev->fd);
   } else {

      if (dev->host_addr)
         free((void *)dev->host_addr);
   }


   dev_init(dev);
}
