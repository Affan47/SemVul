http_job_failed (GVfsJob *job, SoupMessage *msg)
{
  switch (msg->status_code) {

  case SOUP_STATUS_NOT_FOUND:
    g_vfs_job_failed_literal (job, G_IO_ERROR, G_IO_ERROR_NOT_FOUND,
                              msg->reason_phrase);
    break;

  case SOUP_STATUS_UNAUTHORIZED:
  case SOUP_STATUS_PAYMENT_REQUIRED:
  case SOUP_STATUS_FORBIDDEN:
    g_vfs_job_failed (job, G_IO_ERROR, G_IO_ERROR_PERMISSION_DENIED,
                      _("HTTP Client Error: %s"), msg->reason_phrase);
    break;
  default:
    g_vfs_job_failed (job, G_IO_ERROR, G_IO_ERROR_FAILED,
                      _("HTTP Error: %s"), msg->reason_phrase);
  }
}
