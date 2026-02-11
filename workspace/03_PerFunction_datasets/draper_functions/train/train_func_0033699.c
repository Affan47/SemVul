addToConfig(ArConfig *config,
					       const char *sectionName,
					       const char *prefix)
{
  std::string name;

  config->addSection(ArConfig::CATEGORY_ROBOT_OPERATION,
                     sectionName,
                     "");

  config->addParam(ArConfigArg(ArConfigArg::SEPARATOR), sectionName,
		     ArPriority::FACTORY);
  name = prefix;
  name += "AngleSpread";
  config->addParam(
	  ArConfigArg(name.c_str(), &myAngleToCheck,
	      "Filter settings.  The angle spread to check on either side of each reading",
		      0),
	  sectionName, ArPriority::FACTORY);

  name = prefix;
  name += "AnyNeighborFactor";
  config->addParam(
	  ArConfigArg(name.c_str(), &myAnyFactor,
	      "Filter settings.  If a reading (decided by the anglespread) is further than any of its neighbor reading times this factor, it is ignored... so a value between 0 and 1 will check if they're all closer, a value greater than 1 will see if they're all further, negative values means this factor won't be used",
		      -1),
	  sectionName, ArPriority::FACTORY);

  name = prefix;
  name += "AllNeighborFactor";
  config->addParam(
	  ArConfigArg(name.c_str(), &myAllFactor,
	      "Filter settings.  If a reading (decided by the anglespread) is further than all of its neighbor reading times this factor, it is ignored... so a value between 0 and 1 will check if they're all closer, a value greater than 1 will see if they're all further, negative values means this factor won't be used",
		      -1),
	  sectionName, ArPriority::FACTORY);

  config->addParam(ArConfigArg(ArConfigArg::SEPARATOR), sectionName,
		   ArPriority::FACTORY);

  name = prefix;
  name += "AnyNeighborMinRange";
  config->addParam(
	  ArConfigArg(name.c_str(), &myAnyMinRange,
	      "Filter settings.  If a reading itself, or if it has a neighbor (decided by the anglespread) that is closer than this value (in mm) it is ignored... negative values means this factor won't be used",
		      -1),
	  sectionName, ArPriority::FACTORY);

  name = prefix;
  name += "AnyNeighborMinRangeLessThanAngle";
  config->addParam(
	  ArConfigArg(name.c_str(), &myAnyMinRangeLessThanAngle,
	      "Filter settings.  The AnyNeighborMinRange will only be applied to angles LESS than this (so the AnyNeighborMinRange filter will only apply angles below this, or above GreatestAngle)"),
	  sectionName, ArPriority::FACTORY);

  name = prefix;
  name += "AnyNeighborMinRangeGreaterThanAngle";
  config->addParam(
	  ArConfigArg(name.c_str(), &myAnyMinRangeGreaterThanAngle,
	      "Filter settings.  The AnyNeighborMinRange will only be applied to angles GREATER than this (so the AnyNeighborMinRange filter will only apply above this, or below LeastAngle)"),
	  sectionName, ArPriority::FACTORY);

  config->addParam(ArConfigArg(ArConfigArg::SEPARATOR), sectionName,
		   ArPriority::FACTORY);

}
