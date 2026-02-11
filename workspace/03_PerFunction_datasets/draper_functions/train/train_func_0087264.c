pipe_loader_sw_probe(struct pipe_loader_device **devs, int ndev)
{
   int i;

   for (i = 0; i < Elements(backends); i++) {
      if (i < ndev) {
         struct pipe_loader_sw_device *sdev = CALLOC_STRUCT(pipe_loader_sw_device);

         sdev->base.type = PIPE_LOADER_DEVICE_SOFTWARE;
         sdev->base.driver_name = "swrast";
         sdev->base.ops = &pipe_loader_sw_ops;
         sdev->ws = backends[i]();
         devs[i] = &sdev->base;
      }
   }

   return i;
}
