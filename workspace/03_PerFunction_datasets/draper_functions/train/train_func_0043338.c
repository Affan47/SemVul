internalize_node(::CosStream::StreamIO_ptr sio, ::CosLifeCycle::FactoryFinder_ptr there, ::CosGraphs::Node::Roles_out rolesOfNode)
{
  _0RL_cd_b67f6a068d22986b_93000000 _call_desc(_0RL_lcfn_b67f6a068d22986b_a3000000, "internalize_node", 17);
  _call_desc.arg_0 = sio;
  _call_desc.arg_1 = there;

  _invoke(_call_desc);
  rolesOfNode = _call_desc.arg_2._retn();


}
