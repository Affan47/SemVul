add_chunk(DOH *ns, DOH *chunk, int allow) {
  DOH *echunk;
  Seek(chunk, 0, SEEK_SET);
  if (allow) {
    echunk = Preprocessor_replace(chunk);
    addline(ns, echunk, allow);
    Delete(echunk);
  } else {
    addline(ns, chunk, 0);
  }
  Clear(chunk);
}
