is_attribute (CAttributeInfo *obj) {
  if (obj->isAnonymous () ||
      obj->EnumeratorInfo () ||


      (obj->TypeInfo () &&
       (obj->TypeInfo ()->isBitField() ||
        (obj->TypeInfo ()->Record () && obj->TypeInfo ()->Record ()->isAnonymous ()) ||
        (obj->TypeInfo ()->EnumInfo () && obj->TypeInfo ()->EnumInfo ()->isAnonymous ()))))
    return false;
  return true;
}
