advance()
{
  QTime time;
  time.restart();
  int duration = createAnimation(true);

  kDebug() << "ADVANCE: Restarting timer in " << (duration+5000) <<" creation time " << time.elapsed();
  mTimer->start(duration + 5000);
}
