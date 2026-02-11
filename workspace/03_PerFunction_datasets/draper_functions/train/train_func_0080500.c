save(Document *doc) {
  assert(doc != NULL);

  if (doc->get_readonly()) {
    katoob_error(_("This document can not be saved. It's a read only file."));
    return true;
  }

  if (doc->has_file()) {
    return doc->save();
  }

  return save(true);
}
