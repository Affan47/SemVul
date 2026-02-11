AddElement(XmlElement *child) {
  if (child == NULL)
    return;

  XmlChild ** pprev = last_child_ ? &(last_child_->next_child_) : &first_child_;
  *pprev = child;
  last_child_ = child;
  child->next_child_ = NULL;
}
