dev_remap(char *name,struct vdevice *orig,
                          m_uint64_t paddr,m_uint32_t len)
{
   struct vdevice *dev;

   if (!(dev = dev_create(name)))
      return NULL;

   dev->phys_addr  = paddr;
   dev->phys_len   = len;
   dev->flags      = orig->flags | VDEVICE_FLAG_REMAP;
   dev->fd         = orig->fd;
   dev->host_addr  = orig->host_addr;
   dev->handler    = orig->handler;
   dev->sparse_map = orig->sparse_map;
   return dev;
}
