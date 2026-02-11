startTable(const TableNIC &nic)
{
  startDisplay(nic);
  start();
  if (tableLevel_++) {
    mgr_->message(RtfMessages::nestedTable);
    return;
  }
  if (nic.widthType == TableNIC::widthExplicit)
    tableWidth_ = computeLengthSpec(nic.width);
  else
    tableWidth_ = (displaySize_
                   - specFormat_.leftIndent
		   - specFormat_.rightIndent);
  tableDisplaySize_ = displaySize_;
  tableLeftIndent_ = specFormat_.leftIndent;
  tableRightIndent_ = specFormat_.rightIndent;
  tableAlignment_ = specFormat_.displayAlignment;
  switch (tableAlignment_) {
  case 'r':
    if (tableRightIndent_ != 0) {
      tableAlignment_ = 'l';
      tableLeftIndent_ = tableDisplaySize_ - tableWidth_ - tableRightIndent_;
    }
    break;
  case 'c':
    if (tableLeftIndent_ != 0 || tableRightIndent_ != 0) {
      tableAlignment_ = 'l';
      tableLeftIndent_ = (tableDisplaySize_ - tableWidth_ + tableLeftIndent_ - tableRightIndent_)/2;
    }
    break;
  default:
    break;
  }
}
