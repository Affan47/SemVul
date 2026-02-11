CongInit(IBFabric *p_fabric)
{
   if (CongFabrics.find(p_fabric) != CongFabrics.end())
   {
      cout << "-E- Congestion Tracker already initialized" << endl;
      return(1);
   }

   CongFabrics[p_fabric] = CongFabricData();
   map_pport_paths &portPaths = CongFabrics[p_fabric].portPaths;


   IBNode *p_node;
   IBPort *p_port;
   for( map_str_pnode::iterator nI = p_fabric->NodeByName.begin();
        nI != p_fabric->NodeByName.end();
        nI++)
   {
      p_node = (*nI).second;
		if (p_node->rank > CongFabrics[p_fabric].maxRank)
			CongFabrics[p_fabric].maxRank = p_node->rank;

      for( unsigned int pn = 1; pn <= p_node->numPorts; pn++)
      {
         p_port = p_node->getPort(pn);
         if (!p_port || ! p_port->p_remotePort) continue;

         portPaths[p_port] = list_src_dst();
      }
   }
   return(0);
}
