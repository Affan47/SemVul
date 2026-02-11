moveArmiesAction()
{
  kDebug();
  bool res = Move();
  kDebug() << "Move got " << res;
  return res;
}
