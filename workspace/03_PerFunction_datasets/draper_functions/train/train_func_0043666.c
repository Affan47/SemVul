vmw_fence_signalled(struct vmw_winsys_screen *vws,
		   struct pipe_fence_handle *fence,
		   unsigned flag)
{
   struct vmw_fence *vfence;
   int32_t vflags = SVGA_FENCE_FLAG_EXEC;
   int ret;
   uint32_t old;

   if (!fence)
      return 0;

   vfence = vmw_fence(fence);
   old = p_atomic_read(&vfence->signalled);

   vflags &= ~vfence->mask;

   if ((old & vflags) == vflags)
      return 0;


#if 1
   ret = vmw_ioctl_fence_signalled(vws, vfence->handle, vflags);

   if (ret == 0)
      p_atomic_set(&vfence->signalled, 1);
   return ret;
#else
   (void) ret;
   return -1;
#endif
}
