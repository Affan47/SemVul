_e_fm2_client_mount(const char *udi, const char *mountpoint)
{
   char *d;
   int l, l1, l2 = 0;

   if (!udi)
     return 0;

   l1 = strlen(udi);
   if (mountpoint)
     {
        l2 = strlen(mountpoint);
        l = l1 + 1 + l2 + 1;
     }
   else
     l = l1 + 1;
   d = alloca(l);
   strcpy(d, udi);
   if (mountpoint)
     strcpy(d + l1 + 1, mountpoint);

   return _e_fm_client_send_new(E_FM_OP_MOUNT, (void *)d, l);
}
