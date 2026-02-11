batteryAddCreator(
	const char *batteryType,
	ArRetFunctor2<ArBatteryMTX *, int, const char *> *creator)
{
  if (ourBatteryCreatorMap.find(batteryType) != ourBatteryCreatorMap.end())
  {
    ArLog::log(ArLog::Normal, "Aria::batteryAddCreator: There is already a battery creator for %s, replacing it", batteryType);
    ourBatteryCreatorMap.erase(batteryType);
  }
  else
  {


    if (!ourBatteryTypes.empty())
      ourBatteryChoices += ";;";
    ourBatteryChoices += batteryType;

    if (!ourBatteryTypes.empty())
      ourBatteryTypes += "|";
    ourBatteryTypes += batteryType;
  }

  ourBatteryCreatorMap[batteryType] = creator;
  return true;
}
