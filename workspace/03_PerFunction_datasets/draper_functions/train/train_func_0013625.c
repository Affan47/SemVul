setAttributeItem(unsigned Attribute, unsigned Value,
                        bool OverwriteExisting) {

    if (AttributeItem *Item = getAttributeItem(Attribute)) {
      if (!OverwriteExisting)
        return;
      Item->Type = AttributeItem::NumericAttribute;
      Item->IntValue = Value;
      return;
    }


    AttributeItem Item = {
      AttributeItem::NumericAttribute,
      Attribute,
      Value,
      StringRef("")
    };
    Contents.push_back(Item);
  }
