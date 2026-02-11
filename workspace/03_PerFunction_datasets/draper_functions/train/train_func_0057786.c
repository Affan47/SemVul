timeout_countdown(gpointer data)
{
  SAVE_SESS *sess = (SAVE_SESS *)data;

  if (!sess->countdown) {
    cb_ok(NULL, data);
    return FALSE;
  }

  sess->countdown--;
  disp_countdown(sess);
  return TRUE;
}
