restoreSerialPort()
{
  if (!is_usb && jtagBox >= 0 && oldtioValid)
      tcsetattr(jtagBox, TCSANOW, &oldtio);
}
