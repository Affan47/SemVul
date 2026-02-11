parseSound(Object *obj)
{


  Stream *str = NULL;

  if (obj->isStream()) {
    str = obj->getStream();
  } else {
    return NULL;
  }

  Dict *dict = str->getDict();
  if (dict == NULL)
    return NULL;
  Object tmp;

  dict->lookup("R", &tmp);
  if (tmp.isNum()) {
    return new Sound(obj);
  } else {
    return NULL;
  }
}
