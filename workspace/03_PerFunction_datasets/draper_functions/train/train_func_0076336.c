dispatchWinmessCallback()
{
  if (!s_windowRun)return;

  dispatchGemWindowMessages(GemMan::getWindowInfo());

  clock_delay(s_windowClock, s_windowDelTime);
}
