invalidate()
{
  ArScopedLock lockc(ourCPUMutex);
  ArScopedLock lockw(ourWirelessMutex);
  ourShouldRefreshCPU = ourShouldRefreshWireless = true;
}
