_handle_flicksoup_error (FrogrController *self, GError *error, gboolean notify_user)
{
  FrogrControllerPrivate *priv = FROGR_CONTROLLER_GET_PRIVATE (self);
  void (* error_function) (GtkWindow *, const gchar *) = NULL;
  gchar *msg = NULL;
  gchar *video_quota_msg = NULL;
  gint n_videos = 0;

  error_function = frogr_util_show_error_dialog;
  switch (error->code)
    {
    case FSP_ERROR_CANCELLED:
      msg = g_strdup (_("Process cancelled"));
      error_function = NULL;
      break;

    case FSP_ERROR_NETWORK_ERROR:
      msg = g_strdup (_("Connection error:\nNetwork not available"));
      break;

    case FSP_ERROR_CLIENT_ERROR:
      msg = g_strdup (_("Connection error:\nBad request"));
      break;

    case FSP_ERROR_SERVER_ERROR:
      msg = g_strdup (_("Connection error:\nServer-side error"));
      break;

    case FSP_ERROR_UPLOAD_INVALID_FILE:
      msg = g_strdup (_("Error uploading:\nFile invalid"));
      break;

    case FSP_ERROR_UPLOAD_QUOTA_PICTURE_EXCEEDED:
      msg = g_strdup (_("Error uploading picture:\nQuota exceeded"));
      break;

    case FSP_ERROR_UPLOAD_QUOTA_VIDEO_EXCEEDED:
      n_videos = frogr_account_get_current_videos (priv->account);
      video_quota_msg = g_strdup_printf (ngettext ("Quota exceeded (limit: %d video per month)",
                                                   "Quota exceeded (limit: %d videos per month)", n_videos),
                                         n_videos);
      msg = g_strdup_printf ("%s\n%s",
                             _("Error uploading video:\nYou can't upload more videos with this account"),
                             video_quota_msg);
      g_free (video_quota_msg);
      break;

    case FSP_ERROR_PHOTO_NOT_FOUND:
      msg = g_strdup (_("Error:\nPhoto not found"));
      break;

    case FSP_ERROR_PHOTOSET_PHOTO_ALREADY_IN:
      msg = g_strdup (_("Error:\nPhoto already in photoset"));
      break;

    case FSP_ERROR_GROUP_PHOTO_ALREADY_IN:
      msg = g_strdup (_("Error:\nPhoto already in group"));
      break;

    case FSP_ERROR_GROUP_PHOTO_IN_MAX_NUM:
      msg = g_strdup (_("Error:\nPhoto already in the maximum number of groups possible"));
      break;

    case FSP_ERROR_GROUP_LIMIT_REACHED:
      msg = g_strdup (_("Error:\nGroup limit already reached"));
      break;

    case FSP_ERROR_GROUP_PHOTO_ADDED_TO_QUEUE:
      msg = g_strdup (_("Error:\nPhoto added to group's queue"));
      break;

    case FSP_ERROR_GROUP_PHOTO_ALREADY_IN_QUEUE:
      msg = g_strdup (_("Error:\nPhoto already added to group's queue"));
      break;

    case FSP_ERROR_GROUP_CONTENT_NOT_ALLOWED:
      msg = g_strdup (_("Error:\nContent not allowed for this group"));
      break;

    case FSP_ERROR_AUTHENTICATION_FAILED:
      msg = g_strdup_printf (_("Authorization failed.\nPlease try again"));
      error_function = _show_auth_failed_dialog_and_retry;
      break;

    case FSP_ERROR_NOT_AUTHENTICATED:
      frogr_controller_revoke_authorization (self);
      msg = g_strdup_printf (_("Error\n%s is not properly authorized to upload pictures "
                               "to Flickr.\nPlease re-authorize it"), APP_SHORTNAME);
      break;

    case FSP_ERROR_OAUTH_UNKNOWN_ERROR:
      msg = g_strdup_printf (_("Unable to authenticate in Flickr\nPlease try again."));
      break;

    case FSP_ERROR_OAUTH_NOT_AUTHORIZED_YET:
      msg = g_strdup_printf (_("You have not properly authorized %s yet.\n"
                               "Please try again."), APP_SHORTNAME);
      break;

    case FSP_ERROR_OAUTH_VERIFIER_INVALID:
      msg = g_strdup_printf (_("Invalid verification code.\nPlease try again."));
      break;

    case FSP_ERROR_SERVICE_UNAVAILABLE:
      msg = g_strdup_printf (_("Error:\nService not available"));
      break;

    default:

      msg = g_strdup_printf (_("An error happened: %s."), error->message);
    }

  if (notify_user && error_function)
    error_function (GTK_WINDOW (priv->mainview), msg);

  DEBUG ("%s", msg);
  g_free (msg);
}
