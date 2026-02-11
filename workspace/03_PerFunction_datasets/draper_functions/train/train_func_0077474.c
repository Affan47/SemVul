parseAction(Object *obj, GooString *baseURI) {
  LinkAction *action;
  Object obj2, obj3, obj4;

  if (!obj->isDict()) {
      error(-1, "parseAction: Bad annotation action for URI '%s'",
            baseURI ? baseURI->getCString() : "NULL");
      return NULL;
  }

  obj->dictLookup("S", &obj2);


  if (obj2.isName("GoTo")) {
    obj->dictLookup("D", &obj3);
    action = new LinkGoTo(&obj3);
    obj3.free();


  } else if (obj2.isName("GoToR")) {
    obj->dictLookup("F", &obj3);
    obj->dictLookup("D", &obj4);
    action = new LinkGoToR(&obj3, &obj4);
    obj3.free();
    obj4.free();


  } else if (obj2.isName("Launch")) {
    action = new LinkLaunch(obj);


  } else if (obj2.isName("URI")) {
    obj->dictLookup("URI", &obj3);
    action = new LinkURI(&obj3, baseURI);
    obj3.free();


  } else if (obj2.isName("Named")) {
    obj->dictLookup("N", &obj3);
    action = new LinkNamed(&obj3);
    obj3.free();


  } else if (obj2.isName("Movie")) {
    action = new LinkMovie(obj);


  } else if (obj2.isName("Rendition")) {
    action = new LinkRendition(obj);


  } else if (obj2.isName("Sound")) {
    action = new LinkSound(obj);


  } else if (obj2.isName("JavaScript")) {
    obj->dictLookup("JS", &obj3);
    action = new LinkJavaScript(&obj3);
    obj3.free();


  } else if (obj2.isName()) {
    action = new LinkUnknown(obj2.getName());


  } else {
    error(-1, "parseAction: Unknown annotation action object: URI = '%s'",
          baseURI ? baseURI->getCString() : "NULL");
    action = NULL;
  }

  obj2.free();

  if (action && !action->isOk()) {
    delete action;
    return NULL;
  }
  return action;
}
