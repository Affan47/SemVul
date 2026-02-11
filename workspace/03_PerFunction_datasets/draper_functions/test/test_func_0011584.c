buildContent() {
  addHeadline("General", 4);
  startTable(1, RELATIVE, 100, RELATIVE, 100);
  addConstructionCosts();
  addTREntry("Construction Steps", bt.construction_steps);
  addTREntry("BuildingLevel", getHeightImgString(bt.height));
  endTable();

  addHeadline("Terrain access", 4);
  IntVec iv;
  iv.push_back(37);
  iv.push_back(21);
  iv.push_back(21);
  iv.push_back(21);
  startTable(1, RELATIVE, 100, NONE, 0, VOID, "", &iv);
  *buildingInfStream << "<tr>";
  addTitle("Terrain Type");
  addTitle("Constructable on");
  addTitle("Not Constructable on");
  addTitle("Fatal");
  *buildingInfStream << "</tr>" << endl;
  for(int i=0; i< terrainPropertyNum; i++) {
    ASCString terrain = terrainProperty[i];

    if (( bt.terrainaccess.terrain.test(i) )|| ( bt.terrainaccess.terrainnot.test(i) )
        || ( bt.terrainaccess.terrainkill.test(i) )) {


      if ( bt.terrainaccess.terrain.test(i) ) {
        addTREntry(terrain, constructImageLink(STDGFXPATH + ASCString("haken.gif"), "YES") + "<td class=\"wg\"></td><td class=\"wg\">" );
      }


      if ( bt.terrainaccess.terrainnot.test(i) ) {
        addTREntry(terrain, "</td> <td class=\"wg\">" + constructImageLink(STDGFXPATH + ASCString("hakenrot.gif"), "YES") + "<td class=\"wg\">");
      }
      if ( bt.terrainaccess.terrainkill.test(i) ) {
        addTREntry(terrain, "</td> <td class=\"wg\"></td> <td class=\"wg\">" + constructImageLink(STDGFXPATH + ASCString ("hakenrot.gif"), "YES"));
      }
    }
  }
  endTable();
}
