parent_ptr()
  {
    return parent->left == this ? &parent->left : &parent->right;
  }
