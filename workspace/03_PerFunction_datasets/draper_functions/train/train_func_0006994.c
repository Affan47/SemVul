release_underlying()
{
  if(dtd_)
  {


    xmlDtd* dtd=dtd_->cobj();
    Node::free_wrappers(reinterpret_cast<xmlNode*>(dtd));
    xmlFreeDtd(dtd);
    dtd_ = 0;
  }
}
