globus_l_object_read_copy (void *srcvp, void **dstvpp)
{
  globus_object_read_instance_t *src, *dst;
  if (srcvp==NULL || dstvpp==NULL) return;
  src = ((globus_object_read_instance_t *) srcvp);
  (*dstvpp) = globus_malloc (sizeof(globus_object_read_instance_t));
  dst = ((globus_object_read_instance_t *) (*dstvpp));
  if (dst==NULL) return;
  dst->read_resource = globus_object_copy(src->read_resource);
  dst->read_offset = src->read_offset;
  dst->read_size = src->read_size;
}
