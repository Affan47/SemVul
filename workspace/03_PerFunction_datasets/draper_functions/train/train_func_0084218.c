startTablePart(const FOTBuilder::TablePartNIC &nic,
				      FOTBuilder *&header, FOTBuilder *&footer)
{
  save_.insert(new SaveFOTBuilder);
  footer = save_.head();
  save_.insert(new SaveFOTBuilder);
  header = save_.head();
  startTablePartSerial(nic);
}
