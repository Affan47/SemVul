setName(Init *NewName) {
  if (TrackedRecords.getDef(Name->getAsUnquotedString()) == this) {
    TrackedRecords.removeDef(Name->getAsUnquotedString());
    TrackedRecords.addDef(this);
  } else if (TrackedRecords.getClass(Name->getAsUnquotedString()) == this) {
    TrackedRecords.removeClass(Name->getAsUnquotedString());
    TrackedRecords.addClass(this);
  }
  Name = NewName;
  checkName();


  Init *ComputedName = Name->resolveReferences(*this, 0);
  if (ComputedName != Name) {
    setName(ComputedName);
  }


}
