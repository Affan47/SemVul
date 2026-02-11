show_splashscreen()
{
  splash = new QSplashScreen(this, *pixmap, Qt::WindowStaysOnTopHint);

  splash->show();
}
