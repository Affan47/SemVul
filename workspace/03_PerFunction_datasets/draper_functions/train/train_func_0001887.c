globus_l_error_protocol_violated_copy (void *srcvp, void **dstvpp)
{
  globus_error_protocol_violated_instance_t *src, *dst;
  if (srcvp==NULL || dstvpp==NULL) return;
  src = ((globus_error_protocol_violated_instance_t *) srcvp);
  (*dstvpp) = globus_malloc (sizeof(globus_error_protocol_violated_instance_t));
  dst = ((globus_error_protocol_violated_instance_t *) (*dstvpp));
  if (dst==NULL) return;
  dst->protocol_violated_version = globus_object_copy(src->protocol_violated_version);
}
