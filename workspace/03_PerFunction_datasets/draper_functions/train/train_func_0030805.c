applyTo(const MSTableColumnGroup &group_,const MSTableColumnGroup::ColumnGroupList &)
{
  MSManagedPointer<MSTableColumnGroup> newGroup(new MSTableColumnGroup(group_.table()),MSInit);
  newGroup->shallowCopy(group_);
  _tableGroupList<<newGroup;
  return MSTrue;
}
