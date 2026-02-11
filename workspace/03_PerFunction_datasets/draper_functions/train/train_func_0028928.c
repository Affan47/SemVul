pad_to_width_signed(Design*des, NetNet*net, unsigned wid,
                           const LineInfo&info)
{
      NetScope*scope = net->scope();

      if (net->vector_width() >= wid)
	    return net;

      NetSignExtend*se
	    = new NetSignExtend(scope, scope->local_symbol(), wid);
      se->set_line(info);
      des->add_node(se);

      NetNet*tmp = new NetNet(scope, scope->local_symbol(), NetNet::WIRE, wid);
      tmp->set_line(info);
      tmp->local_flag(true);
      tmp->data_type(net->data_type());
      tmp->set_signed(true);

      connect(tmp->pin(0), se->pin(0));
      connect(se->pin(1), net->pin(0));

      return tmp;
}
