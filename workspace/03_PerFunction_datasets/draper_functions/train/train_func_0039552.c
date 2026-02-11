addSectionLinks() {
  *buildingInfStream << "<td class=\"linksection\" valign=\"top\">" << endl;
  *buildingInfStream << "<p class=\"bgmenu\">" << endl;
  addLink (BuildingMainPage::TITLE, fileName  + MAINLINKSUFFIX + HTML);
  addLink (UnitTerrainPage::TITLE, fileName + MOVEMENTLINKSUFFIX + HTML);
  addLink (UnitWeaponPage::TITLE, fileName + WEAPONLINKSUFFIX + HTML);
  addLink (UnitCargoPage::TITLE, fileName + CARGOLINKSUFFIX + HTML);
  addLink (UnitConstructionPage::TITLE, fileName + CONSTRUCTIONLINKSUFFIX + HTML);
  addLink (UnitResearchPage::TITLE, fileName + RESEARCHLINKSUFFIX + HTML);
  *buildingInfStream << "</p>" << endl;
  *buildingInfStream << "<hr>" << endl;
  *buildingInfStream << "</td>" << endl;
}
