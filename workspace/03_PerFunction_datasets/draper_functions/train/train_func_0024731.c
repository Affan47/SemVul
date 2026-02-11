OnDisconnect() {
  Log(FAILURE, "%s - connection lost !!!", __FUNCTION__);
  Notification(FAILURE, GetLocalizedString(30044));
}
