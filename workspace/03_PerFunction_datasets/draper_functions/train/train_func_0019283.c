DestroyCacheNexus(NexusInfo *nexus_info)
{
  if (nexus_info != (NexusInfo *) NULL)
    {
      MagickFreeAlignedMemory(nexus_info->staging);
      MagickFreeAlignedMemory(nexus_info);
    }
}
