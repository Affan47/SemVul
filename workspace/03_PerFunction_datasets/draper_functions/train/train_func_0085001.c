gftp_copy_param_options (gftp_request * dest_request,
                         gftp_request * src_request)
{
  g_return_if_fail (dest_request != NULL);
  g_return_if_fail (src_request != NULL);
  g_return_if_fail (dest_request->protonum == src_request->protonum);

  if (dest_request->copy_param_options)
    dest_request->copy_param_options (dest_request, src_request);
}
