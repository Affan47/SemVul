_should_retry_operation (GError *error, gint attempts)
{
  if (error->code == FSP_ERROR_CANCELLED
      || error->code == FSP_ERROR_UPLOAD_INVALID_FILE
      || error->code == FSP_ERROR_UPLOAD_QUOTA_PICTURE_EXCEEDED
      || error->code == FSP_ERROR_UPLOAD_QUOTA_VIDEO_EXCEEDED
      || error->code == FSP_ERROR_OAUTH_NOT_AUTHORIZED_YET
      || error->code == FSP_ERROR_NOT_AUTHENTICATED
      || error->code == FSP_ERROR_NOT_ENOUGH_PERMISSIONS
      || error->code == FSP_ERROR_INVALID_API_KEY)
    {

      return FALSE;
    }

  return attempts < MAX_ATTEMPTS;
}
