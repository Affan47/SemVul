addSection(const char *categoryName,
                                    const char *sectionName,
                                    const char *sectionDescription)
{

  if ((categoryName == NULL) || ArUtil::isStrEmpty(sectionName)) {

    ArLog::log(ArLog::Normal,
               "%sFailed to add section '%s' to category '%s'",
               myLogPrefix.c_str(),
               ((sectionName != NULL) ? sectionName : "NULL"),
               ((categoryName != NULL) ? categoryName : "NULL"));
    return false;
  }

  ArConfigSection *section = findSection(sectionName);

  if ((section != NULL) && (!ArUtil::isStrEmpty(section->getCategoryName())))
  {
    translateSection(section);

    ArLog::log(ArLog::Normal,
               "%sFailed to add section '%s' to category '%s', already defined in category '%s'",
               myLogPrefix.c_str(),
               ((sectionName != NULL) ? sectionName : "NULL"),
               ((categoryName != NULL) ? categoryName : "NULL"),
               section->getCategoryName());
    return false;
  }

  if (section == NULL) {
    ArLog::log(ArLog::Verbose, "%sMaking new section '%s' in category '%s'",
               myLogPrefix.c_str(), sectionName, categoryName);

    section = new ArConfigSection(sectionName,
                                  sectionDescription,
                                  myIsQuiet,
                                  categoryName);
    mySections.push_back(section);
  }
  else {
    ArLog::log(ArLog::Verbose, "%sAssigning existing section '%s' to category '%s'",
               myLogPrefix.c_str(), sectionName, categoryName);

    section->setCategoryName(categoryName);
    section->setComment(sectionDescription);
  }
  translateSection(section);


  std::list<std::string> *sectionList = NULL;

  std::map<std::string, std::list<std::string> >::iterator catIter = myCategoryToSectionsMap.find(categoryName);
  if (catIter != myCategoryToSectionsMap.end()) {
    sectionList = &(catIter->second);
  }

  bool isSectionFound = false;
  if (sectionList != NULL) {
    isSectionFound = ArUtil::isStrInList(sectionName, *sectionList);
  }


  if (!isSectionFound) {
    myCategoryToSectionsMap[categoryName].push_back(sectionName);
  }

  return true;

}
