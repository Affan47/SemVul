add_node_to (lto_cgraph_encoder_t encoder, struct cgraph_node *node,
	     bool include_body)
{
  if (node->clone_of)
    add_node_to (encoder, node->clone_of, include_body);
  else if (include_body)
    lto_set_cgraph_encoder_encode_body (encoder, node);
  lto_cgraph_encoder_encode (encoder, node);
}
