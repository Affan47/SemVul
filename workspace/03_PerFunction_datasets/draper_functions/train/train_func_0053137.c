addItem(void * const item,
                       const SbOctTreeFuncs & itemfuncs,
                       const int maxitems)
{
  if (this->isGroup()) {
    for (int i = 0; i < 8; i++) {
      if (itemfuncs.insideboxfunc(item, this->children[i]->nodesize)) {
        this->children[i]->addItem(item, itemfuncs, maxitems);
      }
    }
  }
  else if (this->items.getLength() >= maxitems) {

    if ((this->items.getLength() % (maxitems+1) == maxitems) &&
        this->splitNode(itemfuncs)) {
      this->addItem(item, itemfuncs, maxitems);
    }
    else {
      this->items.append(item);
    }
  }
  else {
    this->items.append(item);
  }
}
