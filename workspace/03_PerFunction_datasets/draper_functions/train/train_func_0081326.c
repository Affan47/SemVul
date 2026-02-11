CallbackAddKey(const cec_keypress &key)
{
  CLockObject lock(m_cbMutex);
  if (m_configuration.callbacks && m_configuration.callbacks->CBCecKeyPress)
  {

    int64_t now = GetTimeMs();
    if (m_lastKeypress.keycode != key.keycode ||
        key.duration > 0 ||
        now - m_iLastKeypressTime >= m_configuration.iDoubleTapTimeoutMs)
    {

      if (key.duration == 0)
        m_iLastKeypressTime = now;
      m_lastKeypress = key;
      m_configuration.callbacks->CBCecKeyPress(m_configuration.callbackParam, key);
    }
  }
}
