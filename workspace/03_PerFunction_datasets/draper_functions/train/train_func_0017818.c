expand()
{
  xmlNodePtr node = xmlTextReaderExpand(impl_);
  if(node)
  if(node)
  {
    Node::create_wrapper(node);
    return static_cast<Node*>(node->_private);
  }

  check_for_exceptions();
  return 0;
}
