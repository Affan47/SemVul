hwloc_pci_traverse_lookuposdevices_cb(void * cbdata,
				      struct hwloc_obj *pcidev, int depth __hwloc_attribute_unused)
{
  struct hwloc_backend *backend = cbdata;

  if (pcidev->type == HWLOC_OBJ_BRIDGE)
    return;

  hwloc_backends_notify_new_object(backend, pcidev);
}
