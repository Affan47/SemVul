getPriorityName(Priority priority)
{

  if (!ourStringsInited)
  {
    ourPriorityNames[IMPORTANT]     = "Basic";
    ourPriorityNames[NORMAL]        = "Intermediate";
    ourPriorityNames[TRIVIAL]       = "Advanced";
    ourPriorityNames[DETAILED]      = "Advanced";

    ourPriorityNames[EXPERT]        = "Expert";
    ourPriorityNames[FACTORY]       = "Factory";
    ourPriorityNames[CALIBRATION]   = "Calibration";

    for (std::map<ArPriority::Priority, std::string>::iterator iter = ourPriorityNames.begin();
         iter != ourPriorityNames.end();
         iter++) {
      ourNameToPriorityMap[iter->second] = iter->first;
    }

    ourUnknownPriorityName  = "Unknown";
    ourStringsInited        = true;
  }

  std::map<ArPriority::Priority, std::string>::iterator iter =
                                                  ourPriorityNames.find(priority);
  if (iter != ourPriorityNames.end()) {
    return iter->second.c_str();
  }
  else {
    return ourUnknownPriorityName.c_str();
  }
}
