numActiveRCPNodes()
{

  TEUCHOS_TEST_FOR_EXCEPT(0==rcp_node_list());
  return rcp_node_list()->size();
  return 0;
}
