id3v2_get_field(const FXchar * field,FXStringList & list) {
  FXASSERT(field);
  FXASSERT(id3v2);
  if (id3v2->frameListMap().contains(field) && !id3v2->frameListMap()[field].isEmpty() ) {
    TagLib::ID3v2::TextIdentificationFrame * frame = dynamic_cast<TagLib::ID3v2::TextIdentificationFrame*>(id3v2->frameListMap()[field].front());
    TagLib::StringList fieldlist = frame->fieldList();
    for(TagLib::StringList::ConstIterator it = fieldlist.begin(); it != fieldlist.end(); it++) {
      list.append(it->toCString(true));
      }
    }
  else {
    list.clear();
    }
  }
