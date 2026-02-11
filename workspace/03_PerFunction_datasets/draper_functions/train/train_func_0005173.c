operator<<(QDataStream& stream, const Goal& goal)
{
  kDebug() << "Goal operator<< : type" << goal.type()<< endl;
  stream << quint32(goal.type());
  if (goal.player() != 0)
  {
    kDebug() << "Goal operator<< : player " << goal.player()->id() << endl;
    stream << quint32(goal.player()->id());
  }
  else
  {
    kDebug() << "Goal operator<< : player " << 0 << endl;
    stream << quint32(0);
  }
  kDebug() << "Goal operator<< : description " << goal.description() << endl;
  stream << goal.description();
  QList<QString>::ConstIterator it, it_end;
  QList<QString>::ConstIterator itc, itc_end;
  switch (goal.type())
  {
  case Goal::GoalPlayer :
    kDebug() << "Goal operator<< : players " << goal.players().size() << endl;
    stream << quint32(goal.players().size());
    it = goal.players().constBegin(); it_end = goal.players().constEnd();
    for (; it != it_end; it++)
    {
      kDebug() << "Goal operator<< : player " << (*it) << endl;
      stream << *it;
    }
    kDebug() << "Goal operator<< : nbCountries " << goal.nbCountries() << endl;
    stream << quint32(goal.nbCountries());
    break;
  case Goal::Countries:
    kDebug() << "Goal operator<< : nbCountries " << goal.nbCountries() << endl;
    stream << quint32(goal.nbCountries());
    kDebug() << "Goal operator<< : nbArmiesByCountry " << goal.nbArmiesByCountry() << endl;
    stream << quint32(goal.nbArmiesByCountry());
    break;
  case Goal::Continents:
    kDebug() << "Goal operator<< : continents " << goal.continents().size() << endl;
    stream << quint32(goal.continents().size());
    itc = goal.continents().constBegin(); itc_end = goal.continents().constEnd();
    for (; itc != itc_end; itc++)
    {
      kDebug() << "Goal operator<< : continent " << (*itc) << endl;
      stream << (*itc);
    }
    break;
  default: break;
  }
  return stream;
}
