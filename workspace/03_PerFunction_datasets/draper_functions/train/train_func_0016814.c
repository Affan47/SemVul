gst_dccp_create_new_socket (GstElement * element)
{
  int sock_fd;
  if ((sock_fd = socket (AF_INET, SOCK_DCCP, IPPROTO_DCCP)) < 0) {
    GST_ELEMENT_ERROR (element, RESOURCE, OPEN_READ, (NULL), GST_ERROR_SYSTEM);
  }

  return sock_fd;
}
