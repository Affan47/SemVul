getChildNode     (int i) const { if ((!d)||(i>=d->nChild    )) return emptyXMLNode;      return d->pChild[i];     }
