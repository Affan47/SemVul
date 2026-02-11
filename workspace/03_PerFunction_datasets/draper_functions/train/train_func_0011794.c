endHierarchyElement(void *userData, const char *inElementName){
  CAcHierarchy* lCaller((CAcHierarchy*)userData);
  if(string(inElementName)
     ==
     string("reference-tree")){
    {
      lCaller->popNodeAndRegisterEdge();
    }
  }

  if(string(inElementName)
     ==
     string("hierarchy-browser")){
    {

    }
  }

  cout << "</"
       << inElementName
       << " >"
       << endl;
}
