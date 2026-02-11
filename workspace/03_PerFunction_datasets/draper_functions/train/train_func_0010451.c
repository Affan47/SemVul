hwloc_xml_callbacks_register(struct hwloc_xml_component *comp)
{
  if (!hwloc_nolibxml_callbacks)
    hwloc_nolibxml_callbacks = comp->nolibxml_callbacks;
  if (!hwloc_libxml_callbacks)
    hwloc_libxml_callbacks = comp->libxml_callbacks;
}
