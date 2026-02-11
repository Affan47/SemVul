formatBytes(const long long lBytes)
{
   QString strRet;

   const QLocale locale(QLocale::system());

   if (lBytes < KILO)
      strRet = locale.toString(lBytes);
   else if (lBytes < MEGA)
      strRet = locale.toString(static_cast<double>(lBytes) / KILO, 'f', 3) + " KB";
   else if (lBytes < GIGA)
      strRet = locale.toString(static_cast<double>(lBytes) / MEGA, 'f', 3) + " MB";
   else
      strRet = locale.toString(static_cast<double>(lBytes) / GIGA, 'f', 3) + " GB";

   return(strRet);
}
