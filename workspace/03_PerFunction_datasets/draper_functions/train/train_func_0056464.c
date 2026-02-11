hwloc_pci_find_cap(const unsigned char *config, unsigned cap)
{
  unsigned char seen[256] = { 0 };
  unsigned char ptr;

  if (!(config[HWLOC_PCI_STATUS] & HWLOC_PCI_STATUS_CAP_LIST))
    return 0;

  for (ptr = config[HWLOC_PCI_CAPABILITY_LIST] & ~3;
       ptr;
       ptr = config[ptr + HWLOC_PCI_CAP_LIST_NEXT] & ~3) {
    unsigned char id;


    if (seen[ptr])
      break;
    seen[ptr] = 1;

    id = config[ptr + HWLOC_PCI_CAP_LIST_ID];
    if (id == cap)
      return ptr;
    if (id == 0xff)
      break;
  }
  return 0;
}
