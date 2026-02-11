get(Record *R) {
  return &dynamic_cast<RecordRecTy&>(*R->getDefInit()->getType());
}
